# HTTP Handling

This section explains the HTTP behavior implemented by `webserv`, including request parsing, routing, and response creation.

## Supported HTTP methods

The server supports:
- `GET` for retrieving static files and directory indexes
- `HEAD` for retrieving headers without a body
- `POST` for file uploads and CGI request bodies
- `DELETE` for deleting filesystem resources

The request lifecycle is handled primarily by these classes:
- `Server`
- `Request`
- `Response`
- `Config`
- `Location`

## Request parsing

`Server::handleRead()` reads from a client socket in non-blocking mode using `recv()`.
The raw bytes are appended to a `Request` instance stored per client.

`Request` is a state machine with these states:
- `READING_HEADERS`
- `READING_BODY`
- `COMPLETE`
- `ERROR`

It parses:
- request line (`METHOD PATH VERSION`)
- HTTP headers
- body payloads
- optional chunked transfer encoding

If parsing fails or the body exceeds configured limits, `Request` becomes `ERROR` and the server sends an appropriate error response.

## Configuration and routing

`Config` loads the global server configuration along with `Location` entries.
Each `Location` may define:
- `root`
- `index`
- `redirect`
- `upload_store`
- `methods`
- `autoindex`
- `client_max_body_size`
- `cgi_path`

The server matches the request path against locations using prefix matching and chooses the most specific match.

### Path resolution

The server resolves an active root for the request from either:
- the matched `Location` root, or
- the global `Config` folder root.

It then normalizes the path and checks for directory handling, autoindexing, or redirect behavior.

## Method-specific behavior

### GET

- If the path points to a directory, the server attempts to serve an index file.
- If the directory contains no index and autoindex is enabled, the server generates an HTML directory listing.
- If the requested file exists and is readable, it is returned with the correct `Content-Type` and `Content-Length`.
- If the resource is missing, the server returns `404 Not Found`.

### HEAD

- Works like `GET`, but the body is cleared before building the response.
- Headers remain intact so clients may learn about the resource without receiving content.

### POST

- If a matching `Location` defines an `upload_store`, the request body is saved there using the file name extracted from the request path.
- Otherwise, the body is written directly to the requested resource path.
- On success, the server returns `201 Created`.

### DELETE

- The server checks whether the target filesystem path exists.
- If it does, it calls `unlink()` and returns `200 OK`.
- If the path cannot be found, it returns `404 Not Found`.

## Special request handling

### HTTP redirection

If a `Location` contains a `redirect` directive, the server immediately returns `301 Moved Permanently` and sets the `Location` header.

### Autoindex

If the request path ends with `/` and no index file exists, a directory listing is generated only when `autoindex` is enabled for the location.

### 418 "I'm a teapot"

The server includes a built-in easter egg route for `/coffee` that returns `418 I'm a teapot` with an HTML body.

## Error handling

The server returns standard HTTP error pages for:
- `400 Bad Request`
- `403 Forbidden`
- `404 Not Found`
- `405 Method Not Allowed`
- `413 Payload Too Large`
- `500 Internal Server Error`

When a parse or configuration validation problem occurs, the `Response` object is built with the proper status and a default error page.

## Response generation

`Response` is responsible for:
- status code
- header map
- body content
- building the final HTTP response string

`Server::handleWrite()` sends the response in non-blocking mode using `send()`.
If the entire response is not written in one call, the remaining bytes are kept in `_writeBuffs` and sent on subsequent `POLLOUT` events.

## CGI-involved requests

Requests destined for CGI are detected during route resolution and are forwarded to the CGI subsystem.
When a request matches a CGI extension and the associated method is allowed, the server enters `CGI_READY` state instead of immediately sending a static response.
