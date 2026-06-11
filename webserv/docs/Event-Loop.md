# Event Loop Multiplexing & Non-Blocking I/O Kernel

This section provides a rigorous technical breakdown of the single-threaded, asynchronous I/O multiplexing core implemented within the `Cluster` class.

---

## 1. Architectural Philosophy: Single-Threaded Multiplexing

The core design of `webserv` rejects the traditional "thread-per-connection" or "process-per-request" models. Spawning threads introduces severe operating system overhead due to context-switching, thread-contention, and complex resource locking.

Instead, this server routes all concurrent network activity and Inter-Process Communication (IPC) through a **single execution thread** governed by the **`poll()`** system call.

### System Core Benefits:
* **Zero Synchronization Overhead:** No mutexes, condition variables, or read-write locks are required because data is never accessed concurrently by multiple threads.
* **Determinism & Stability:** Eliminates memory corruption vectors such as data races and deadlocks.
* **Scale-Up Capability:** Efficiently manages thousands of volatile, active connections simultaneously using minimal CPU and memory footprints.

---

## 2. Tracking Matrices (Data Structures)

To coordinate sockets and CGI pipelines across a single vector stream, the `Cluster` class manages a centralized collection array along with specialized associative lookup maps:

* **`std::vector<struct pollfd> _fds`:** The master kernel-monitoring array. Every active descriptor (listeners, clients, and pipes) must register an entry here specifying its target event flags (`POLLIN`, `POLLOUT`).
* **`std::map<int, Server*> _servers`:** Maps a master listening socket file descriptor directly to its corresponding virtual `Server` configuration context.
* **`std::map<int, Server*> _clients`:** Maps an active client connection socket descriptor back to the specific `Server` instance routing its lifecycle.
* **`std::map<int, int> _pipeToClientMap`:** An IPC bridge mapping internal CGI read/write pipe file descriptors back to the originating client socket descriptor awaiting execution results.
* **`std::map<int, std::string> _cgiBuffs`:** Tracks incomplete dynamic output streams, mapping a client socket descriptor to its accumulated CGI stdout text buffer.
* **`std::map<int, size_t> _cgiBytesWritten`:** Tracks the progressive byte count of request bodies pushed into a CGI stdin pipe descriptor across partial write cycles.

---

## 3. The Polling Lifecycle (`Cluster::run`)

The entire server execution frame is contained within an infinite loop inside `Cluster::run()`. Each iteration executes a strict, synchronized multi-step dispatch sequence:



### Step 1: The Kernel Wait Phase
The system invokes `poll(&_fds[0], _fds.size(), timeout)`. This call suspends the server thread, yielding CPU cycles until at least one registered file descriptor flags an event or the timeout threshold expires.

### Step 2: Event Traversal
Upon wake-up, the loop iterates over the `_fds` vector sequentially. For each item, it inspects the `revents` (returned events) bitmask populated by the operating system kernel.

### Step 3: Branch Dispatching
The server evaluates the active descriptor type by cross-referencing its tracking maps and acts accordingly:

---

## 4. Non-Blocking Event Mechanics

To maintain non-blocking safety, no system call (`recv`, `send`, `read`, `write`) is ever allowed to halt thread execution. Every descriptor undergoes immediate non-blocking configuration.

### A. Connection Ingestion (Listening Sockets)
When `POLLIN` fires on a master socket tracked inside `_servers`, a client is attempting to connect.
1. The server calls `accept()` to obtain a new client socket descriptor.
2. It immediately executes `fcntl(client_fd, F_SETFL, O_NONBLOCK)` to enforce non-blocking execution.
3. The descriptor is added to `_fds` with an initial interest flag of `POLLIN`.

### B. Inbound Stream Parsing (Client Sockets + `POLLIN`)
When `POLLIN` fires on an established client socket, `Cluster::_handleClientRead()` delegates data collection to `Server::handleRead()`.
* The server performs a non-blocking `recv()` to extract available bytes, transitioning the client's `Request` state machine.
* If the request transitions to `STATIC_READY`, the server updates the descriptor's interest flags inside `_fds` from `POLLIN` to `POLLOUT` to signal readiness to transmit.
* If it transitions to `CGI_READY`, the server instantiates the CGI pipelines, registers the pipe ends into `_fds`, and maps them inside `_pipeToClientMap`.

### C. Outbound Network Egress (Client Sockets + `POLLOUT`)
When `POLLOUT` fires, the client socket is ready to accept outgoing data. The server calls `Server::handleWrite()` which leverages non-blocking `send()` calls.
* **Partial Write Resolution:** If a large resource (or stress tester spike) saturates the socket's kernel buffer, `send()` transmits only a fraction of the data and returns the partial byte count.
* The server safely slices the sent data, queues the remaining unsent bytes inside `_writeBuffs`, retains the `POLLOUT` flag inside `_fds`, and immediately returns to the event loop. Once the kernel buffer empties, `POLLOUT` fires again, and transmission resumes smoothly.

### D. CGI Pipeline Flow (Pipe Descriptors)
* **`_pipe_in[1]` + `POLLOUT`:** `Cluster::_handleCGIWrite()` pushes chunks of the HTTP request body into the CGI runtime's stdin stream. Once fully sent, the parent closes this pipe end to signal an EOF to the child script.
* **`_pipe_out[0]` + `POLLIN`:** `Cluster::_handleCGIRead()` aggressively harvests chunks of text thrown out by the script into `_cgiBuffs[client_fd]` until an EOF condition (read returning 0) is encountered.

---

## 5. Fault Management & Clean Tear-Down

The event loop processes administrative and failure conditions natively via event bitmasks:

* **`POLLHUP` / `POLLERR` / `POLLNVAL`:** Indicates that a client terminated abruptly, a pipe closed prematurely, or a descriptor encountered a hardware/kernel fault.
* **The Cleanup Protocol:** Whenever a fault is encountered or a request lifecycle ends, `Cluster` executes an isolated tear-down sequence:
  1. The invalid file descriptor is removed from the master `_fds` vector.
  2. The descriptor index is scrubbed from `_clients`, `_servers`, and `_pipeToClientMap` arrays to prevent dangling references.
  3. Any associated CGI pipeline structures are reaped non-blockingly using `waitpid(..., WNOHANG)`, and its temporary text buffers are purged from `_cgiBuffs`.
  4. The system safely calls `close()` on the raw descriptor.
