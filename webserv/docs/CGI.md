# CGI Handling

This section describes how `webserv` executes dynamic CGI scripts and integrates their output into HTTP responses.

## CGI subsystem responsibilities

The CGI subsystem is implemented in `CGI` and coordinated by `Server` and `Cluster`.
Its main tasks are:
- create an isolated child process
- set the CGI environment variables
- stream request bodies into the script
- capture the script output without blocking the main event loop

## CGI execution flow

`Server::_execCompetedOrder()` determines whether a request should be handled by CGI.
It examines configured `Location` entries and checks for extensions that begin with `.`.
If the request path matches a CGI-enabled extension and the HTTP method is allowed, the server creates a new `CGI` instance.

The relevant `Location` fields are:
- `path` containing the CGI file extension (e.g. `/.py`)
- `cgi_path` containing the interpreter path

## CGI class behavior

`CGI` builds an environment array and creates two pipe pairs:
- `_pipe_in[2]` for writing the request body into the child process
- `_pipe_out[2]` for reading the script’s stdout

It then forks a child process and executes the CGI interpreter via `execve()`.
The parent keeps the pipe file descriptors and returns control to the event loop.

## Non-blocking pipe management

`Cluster` adds both CGI pipe ends to the `poll()` array:
- write end with `POLLOUT`
- read end with `POLLIN`

When `CLUSTER` receives `POLLOUT` on the write pipe, `Cluster::_handleCGIWrite()` writes the request body in chunks, tracking bytes written. Once the body is fully sent, the write pipe is closed.

When `POLLIN` arrives on the read pipe, `Cluster::_handleCGIRead()` reads available bytes into `_cgiBuffs[client_fd]`.
When the script closes its output, EOF is detected and `CGI` cleanup begins.

## Parsing CGI output

After the CGI script finishes, `Cluster` parses the raw output stream.
The output is split into headers and body by the first `\r\n\r\n` separator.

Headers are forwarded into the `Response` object. The server supports:
- `Status`
- `Content-Type`
- `Location`
- any additional CGI headers

`Status` is converted to the HTTP response code.
If `Location` is present without a status, the server treats it as a redirect and returns `302 Found`.

If the CGI output contains no headers, it is returned as HTML with `200 OK`.
If the output is empty, the server returns `204 No Content`.

## Error recovery

If the CGI pipe read fails or the script crashes, the server builds a `500 Internal Server Error` response.
The client socket is then switched to `POLLOUT` to send the error page.

`Server::cleanupCgi()` also waits for the child process with `waitpid(..., WNOHANG)` and deletes the CGI tracker.

## Security and isolation

- CGI runs in a child process separate from the main server.
- request body content is passed through a dedicated pipe rather than being loaded directly into the interpreter.
- CGI execution failures do not block the main `poll()` loop.

## Example pipeline

1. client request arrives for `/script.py`
2. `Server` detects CGI extension and creates `CGI`
3. `CGI` forks and execs Python interpreter with environment variables
4. `Cluster` writes request body to CGI stdin via pipe
5. `Cluster` reads CGI stdout via pipe
6. output is parsed and converted to an HTTP response
7. response is sent back to the client
