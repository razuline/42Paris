# Event Loop

This section describes the server’s single-threaded event loop and non-blocking I/O architecture.

## Core design

`webserv` uses a single `poll()` loop to handle all network activity and CGI communication in one thread.
This design avoids thread creation, locking, and shared-memory synchronization.

### Main components

- `Cluster`
- `Server`
- `CGI`

`Cluster` is the central event multiplexer:
- manages listening sockets for server ports
- accepts new client connections
- tracks client sockets and CGI pipes
- uses a single `std::vector<struct pollfd>` to store all active file descriptors

## File descriptor management

`Cluster` keeps these maps:
- `_servers`: listening socket fd → `Server*`
- `_clients`: client socket fd → `Server*`
- `_pipeToClientMap`: CGI pipe fd → client socket fd
- `_cgiBuffs`: client fd → CGI output buffer
- `_cgiBytesWritten`: pipe fd → bytes written so far

Each file descriptor in `_fds` is monitored for events such as `POLLIN`, `POLLOUT`, `POLLERR`, and `POLLHUP`.

## Poll loop behavior

The main loop in `Cluster::run()` performs:
1. `poll()` on `_fds`
2. iterates over all ready descriptors
3. dispatches events based on descriptor type:
   - listening socket: accept new connection
   - client socket + `POLLIN`: read request data
   - client socket + `POLLOUT`: write response data
   - CGI pipe read side + `POLLIN`: read CGI output
   - CGI pipe write side + `POLLOUT`: write request body to CGI

### Accepting connections

New clients are accepted with `accept()` and immediately set to non-blocking mode (`O_NONBLOCK`).
The new client socket is added to `_fds` and associated with the correct virtual `Server`.

### Reading client requests

`Cluster::_handleClientRead()` calls `Server::handleRead()`.
Possible return values:
- `READ_ERROR`: close connection
- `READ_INCOMPLETE`: wait for more data
- `STATIC_READY`: prepare the response for writing
- `CGI_READY`: begin CGI pipe monitoring

When `STATIC_READY` is returned, the client socket switches from `POLLIN` to `POLLOUT`.

### Writing client responses

`Cluster::_handleClientWrite()` calls `Server::handleWrite()`.
If the response is fully written, the socket is switched back to `POLLIN`.
If pipelined requests are already buffered, the server can immediately restart the next request cycle.

### CGI pipe handling

CGI uses two pipes:
- write pipe: server → CGI stdin
- read pipe: CGI stdout → server

`Cluster` registers the CGI pipe endpoints in `_fds` and maps them to the originating client.

When the write pipe is writable, `Cluster::_handleCGIWrite()` sends the request body to the CGI script.
When the read pipe becomes readable, `Cluster::_handleCGIRead()` accumulates script output until EOF.

## Error and cleanup handling

`Cluster` handles events such as `POLLERR`, `POLLHUP`, and `POLLNVAL` by closing the relevant descriptor and cleaning up state.

Closing a client connection also removes any associated CGI pipes and frees server state.

## Non-blocking safety

The server does not block on network or CGI I/O:
- client sockets are non-blocking
- CGI pipes are monitored with `poll()`
- read/write operations handle partial transfers and incomplete conditions

This allows the server to keep accepting and servicing multiple clients concurrently without threads.
