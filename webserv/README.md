*This project has been created as part
of the 42 curriculum by erazumov, esergeev and mchiacha*

# webserv - Buiding a Non-Bocking Web Server in C++98

## 📝 Description
**webserv** is a simple HTTP/1.1 web server written in **C++98**. The goal of this project is to create a server like Nginx that can handle many clients at the same time using only one thread.

To achieve this, the server uses a single **`poll()`** loop. This loop monitors all file descriptors (both sockets and pipes) at the same time for reading and writing. Everything runs in **non-blocking mode** (`O_NONBLOCK`), meaning the server never freezes or waits for a slow client.

### ✨ Features
- **One Loop**: Uses only 1 `poll()` call to manage all network I/O operations.

- **Static Website**: Serves HTML, CSS, and images completely and smoothly.
- **HTTP Methods**: Fully supports `GET`, `POST`, and `DELETE` requests.
- **File Upload**: Allows clients to upload and save files on the server.
- **Directory Listing**: Automatically lists files in a folder (Autoindex) if enabled.
- **CGI Scripts**: Runs dynamic Python scripts using `fork()` and pipes without blocking the main server.
- **Resilience**: Hardened against crashes, handling abrupt disconnections or bad CGI scripts safely.
---

## 📐 Design Choices & Comparisons

Here is why we made specific technical choices in our architecture and how they compare to alternative methods.

### 1. Single-Thread Asynchronous vs Multi-Threaded (Apache style)
Instead of creating a new thread or process for every single client connection, we chose a single-threaded event loop driven by `poll()`.

| Feature | Our Single-Threaded Model (Nginx style) | Multi-Threaded Model (Apache style) |
| :--- | :--- | :--- |
| **Memory Usage** | **Very Low** (Shared memory space, lightweight arrays) | **High** (Each thread requires its own stack memory) |
| **Context Switching**| **Zero CPU waste** (No thread switching overhead) | **High CPU cost** (OS constantly swaps active threads) |
| **Data Safety** | **Safe** (No data races, no complex mutex locks needed) | **Complex** (High risk of deadlocks and race conditions) |

### 2. Why `poll()` instead of `select()`?
The subject allows `select()`, `poll()`, `epoll()`, or `kqueue()`. We selected `poll()` as the best balance for this project.

- **Why not `select()`?** `select()` has a hard limit of **1024** file descriptors maximum. If the server gets hit with massive traffic, it crashes or refuses connections. Also, managing bitmasks (`fd_set`) is less intuitive than arrays.

- **Why `poll()`?** It has **no hard limit** on file descriptors (it scales with system memory). It uses a simple vector array of `struct pollfd` which makes adding, tracking, and updating event flags (like `POLLIN` and `POLLOUT`) clean and direct.
- **Why not `epoll()` / `kqueue()`?** While `epoll` (Linux) and `kqueue` (macOS) are faster for thousands of connections, they are OS-specific. `poll()` is completely portable and cross-platform across all Unix environments.

### 3. Separation of Concerns (Modular Architecture)
We deliberately split the system into three fully decoupled layers:

1. **`Cluster` (The Post Office)**: Only cares about raw File Descriptors, system calls (`poll()`, `accept()`), and routing events. It has zero knowledge of HTTP formatting or Python.

2. **`Server` (The Translator)**: Only cares about the HTTP protocol. It receives raw byte buffers from the `Cluster`, uses `Request` to understand them, and prepares a `Response`.
3. **`CGI` (The Factory)**: Only cares about process isolation (`fork()`, `execve()`) and execution environment scripts.


> **💡 Key Benefit:** If we want to replace `poll()` with `epoll()` in the future, we only need to modify the `Cluster` class. The entire HTTP engine (`Server`) and the script engine (`CGI`) will remain completely untouched.
---

## 🏗️ Architecture & Data Flow

Our server is designed using a **modular architecture**. Each class has one specific job, making the code clean, easy to debug, and highly efficient.

### Core Classes Overview

- **`Cluster`**: The master engine of the server. It runs the main `poll()` loop, manages the array of all file descriptors, and accepts new clients. It does not know anything about HTTP; it only handles raw network events.

- **`Server`**: The brain of the HTTP logic. It receives raw data from the `Cluster`, routes the request to the correct folder, and coordinates the creation of the final response.

- **`Config` & `Location`**: The settings parser. They read the `default.conf` file and store rules like ports, allowed methods, and directory roots.
- **`Request`**: The parser machine. It takes the raw text bytes from the client socket, cuts it into pieces, and extracts the HTTP method (`GET`/`POST`/`DELETE`), the URL, and the headers.
- **`Response`**: The packager. It builds the official HTTP response string (headers + body content) to send back to the user's browser.
- **`CGI`**: The external script runner. It creates a child process (`fork()`) and executes the Python interpreter (`execve()`) to run dynamic scripts safely.

### Data Flow: How a Request Travels

Here is the exact journey of a request inside our class architecture:

1. **`Cluster`** catches a network event (`POLLIN`) on a listening socket ➡️ calls `accept()` ➡️ creates a new client socket and adds it to the `poll()` list.

2. **`Cluster`** detects data coming from the client ➡️ reads the bytes and passes them to the matching **`Server`** instance.

3. **`Server`** uses **`Request`** to parse the raw text data into a structured format.
4. **`Server`** checks the **`Config` / `Location`** rules to find the requested file on the disk.
   - *If it is a static file (HTML/CSS):* **`Server`** reads it and populates **`Response`**.

   - *If it is a `.py` script:* **`Server`** starts **`CGI`**, which forks a child process to run Python. **`Cluster`** reads the script's output asynchronously from a pipe and hands it back to **`Server`**.
5. **`Server`** prepares the final **`Response`** object and tells **`Cluster`** that the client socket is ready for writing (`POLLOUT`).
6. **`Cluster`** activates `send()` to transmit the response bytes back to the browser, then cleans up the memory.

## 👥 Team Distribution & Project Modules

We divided the project into three technical modules so the team could collaborate easily.

### Module 1: Network Engine & Event Loop
**Focus:** Infrastructure and `poll()`
- Manages server sockets, ports setup, and multiple virtual server bindings.

- Implements the central `poll()` event loop to check for reading and writing readiness.
- Handles client life-cycles and safely removes disconnected clients without breaking the loop array.

### Module 2: HTTP Parsing & Routing
**Focus:** Request, Response, and Configuration

- Parses the `default.conf` file to setup routes, error pages, and body size limits.

- Reads raw client data, parses HTTP headers (`GET`/`POST`/`DELETE`), and verifies limits.
- Creates valid HTTP responses with precise status codes and handles large file transmissions in small parts.

### Module 3: CGI Gateway (Dynamic Content)
**Focus:** Executing Scripts

- Detects `.py` files and runs them through isolated `fork()` and `execve()` system calls.

- Uses non-blocking UNIX pipes to pass the request body to the script and read back the output.
- Sets up the exact environment variables matrix needed for standard CGI communication.
- Parses the script's output headers (`Status`, `Content-Type`) before returning the response.

---

## 🛠️ Instructions

### Compilation
To compile the project executable using `c++` and strict flags (`-Wall -Wextra -Werror -std=c++98`), run:
```bash
make