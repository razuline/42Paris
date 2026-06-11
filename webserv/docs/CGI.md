# CGI Subsystem Configuration & Process Lifecycle

This section provides an exhaustive technical analysis of how `webserv` handles dynamic Common Gateway Interface (CGI/1.1) scripts asynchronously using non-blocking file descriptors, process isolation, and safe process reclamation.

---

## 1. Subsystem Core Responsibilities

The CGI subsystem is encapsulated within the `CGI` class and orchestrated by the central event loop (`Cluster`) and virtual server logic (`Server`). Its primary mandates are:
1. **Process Isolation:** Spawning an independent sub-process via `fork()` to run the script interpreter (`execve`), keeping the main server safe from external crashes.
2. **Meta-Variable Construction:** Formulating a strictly compliant environment matrix matching the CGI/1.1 specification.
3. **Asynchronous IPC Pipelines:** Creating unidirectional pipe pairs to channel the HTTP request body into the script and harvest its response without stalling the server.
4. **Zombie Reclamation:** Proactively tracking child PIDs and freeing system resources using non-blocking process reaping.

---

## 2. Core Class Attributes & Architecture

The `CGI` class relies on specific member variables to safely maintain state during an asynchronous execution cycle:

* `std::vector<char*> _env`: A dynamically allocated matrix storing `Key=Value` environmental strings passed to `execve()`.
* `pid_t _pid`: Stores the unique Process ID of the spawned child runtime.
* `int _pipe_in[2]`: Unidirectional pipe matrix handling data flowing **into** the CGI script.
    * `_pipe_in[1]` is the **Write End** held by the Parent (`Cluster`).
    * `_pipe_in[0]` is the **Read End** cloned into the Child's `STDIN`.
* `int _pipe_out[2]`: Unidirectional pipe matrix handling output data flowing **out** of the CGI script.
    * `_pipe_out[1]` is the **Write End** cloned into the Child's `STDOUT`.
    * `_pipe_out[0]` is the **Read End** held by the Parent (`Cluster`).



---

## 3. Detailed Execution Flow (`CGI::execute`)

When `Server::_execCompletedOrder()` matches an active request to a CGI location handler based on file extension matching (e.g., `.bla` or `.py`), it instantiates a `CGI` tracking instance and triggers `CGI::execute()`.

### Step 1: Absolute Path Resolution
The method accepts the relative script and interpreter paths, validating them against the current working directory using `getcwd()`. If a path is relative, it normalizes it into a fully absolute path starting with `/`.

### Step 2: Environment Allocation (`_initEnv`)
The subsystem populates `_env` with the essential parameters extracted from the incoming `Request` instance:
-   **Execution Metadata:** `REQUEST_METHOD`, `SERVER_PROTOCOL=HTTP/1.1`, `GATEWAY_INTERFACE=CGI/1.1`.
-   **Target Routing:** `SCRIPT_FILENAME` (absolute path to script file), `SCRIPT_NAME` (virtual URI path).
-   **Payload Specs:** `CONTENT_LENGTH` (string size of request body) and `CONTENT_TYPE`.
-   **Specialized Tokens:** Custom variables such as `HTTP_COOKIE` and test-specific keys like `HTTP_X_SECRET_HEADER_FOR_TEST`.

### Step 3: Process Forking & Pipeline Splicing
Two pipes are instantiated via `pipe()`. Immediately after, `fork()` splits execution:

#### A. Inside the Child Process (`_pid == 0`)
1.  **Unused End Closures:** The child immediately isolates its context by closing the parent-managed pipe ends: `_pipe_in[1]` and `_pipe_out[0]`.
2.  **Stream Redirection:** `dup2()` links `_pipe_in[0]` directly to `STDIN_FILENO`, and links `_pipe_out[1]` directly to `STDOUT_FILENO`.
3.  **Local Isolation:** The original pipe descriptors are cleanly closed using `close()`.
4.  **Directory Traversal:** The child uses `chdir()` to shift into the specific script repository folder. This step prevents cross-directory file mapping vulnerabilities within local CGI contexts.
5.  **Overlay:** Arguments are constructed (`args[0]` points to the binary path, `args[1]` points to the target script). The system invokes `execve(args[0], args, &_env[0])`.
6.  **Error Fallback:** If `execve()` fails, a hardcoded 500 error string payload is pushed directly out of `STDOUT_FILENO`, and the child terminates via `exit(1)`.

#### B. Inside the Parent Process (`_pid > 0`)
1.  **Immediate Isolation:** The parent closes the child-cloned descriptors: `_pipe_in[0]` and `_pipe_out[1]`.
2.  **Enforcing Non-Blocking Flags:** Crucially, the parent uses `fcntl()` to assign **`O_NONBLOCK`** to both `_pipe_in[1]` (Write end) and `_pipe_out[0]` (Read end).
3.  **Memory Cleanliness:** The dynamic strings within the vector are immediately freed through `_clearEnv()`, keeping memory clean during long event loop lifecycles.
4.  **Yielding:** The method returns `Http::OK` and yields execution back to the `poll()` loop.

---

## 4. Asynchronous Pipeline Integration (`Cluster`)

Rather than blocking to write data or await script completion, the parent hands management over to the event loop. The file descriptors are mapped inside the `Cluster` tracking matrices (`_pipeToClientMap`) and appended into the central `poll()` event vector:

* **`_pipe_in[1]` with `POLLOUT`:** Triggered whenever the system pipe buffer is receptive. `Cluster::_handleCGIWrite()` feeds the incoming request body payload in chunks, tracking bytes written via `_cgiBytesWritten`. Once fully transmitted, the write pipe is closed to transmit an EOF signal to the CGI application.
* **`_pipe_out[0]` with `POLLIN`:** Triggered whenever the CGI runtime flushes out data. `Cluster::_handleCGIRead()` accumulates the incoming stream incrementally into the tracking buffer array `_cgiBuffs[client_fd]` until an EOF condition (read returning 0) is encountered.

---

## 5. CGI Output Parsing & Protocol Resilience

Once an EOF is registered across a CGI read pipe, the raw buffer is parsed.

### Header and Body Splitting
The stream is scanned for the canonical HTTP line delimiter `\r\n\r\n`. Everything preceding the marker is parsed as response headers (e.g., `Status`, `Content-Type`, `Location`), while everything succeeding it is loaded as the payload body into the client's `Response` block.

### The Tester Infinite Loop Fix (`Connection: close`)
High-volume network stress testing tools (such as the School 42 `cgi_tester`) run concurrent workers across overlapping cycles. If a server advertises `HTTP/1.1` but closes the connection socket directly after transmitting a CGI response without explicitly notifying the client via headers, the testing runtime can trap itself in a tight infinite loop, pinning a CPU core at 99.9%.

To ensure perfect evaluation compatibility and clean client tear-downs, the server's `Response::build()` framework evaluates headers right before assembly. If no persistent connection parameters are configured, it automatically appends an explicit **`Connection: close`** token to guarantee that testing runtimes handle socket closures cleanly instead of freezing.

---

## 6. Defensive Resource Safety & Zombie Prevention

To achieve total compliance with strict memory guidelines and system resource constraints, the `CGI` subsystem acts defensively during cleanup or premature object destruction:

1.  **Descriptor Leak Immunity:** The destructor verifies all internal pipe indexes (`_pipe_in` and `_pipe_out`). If any descriptor is not `-1`, `close()` is safely executed.
2.  **Non-Blocking Reaping:** The destructor calls `waitpid(_pid, &status, WNOHANG)`. The **`WNOHANG`** flag allows the parent to poll the state of the child process instantly without blocking the server loop.
3.  **Active Hazard Mitigation:** If `waitpid()` returns `0`, it means the child script is stuck or deadlocked. The destructor safely mitigates this hazard by escalating to a forceful **`kill(_pid, SIGKILL)`**, followed by a blocking `waitpid(_pid, NULL, 0)` to guarantee that the process table entry is cleanly removed from the operating system kernels.
