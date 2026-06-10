# webserv Documentation

This folder contains the implementation documentation for the `webserv` project.
It is organized into three main sections that match the team defense topics:

- `HTTP.md` – HTTP parsing, request routing, response generation, and server behavior.
- `Event-Loop.md` – Non-blocking network event loop architecture using `poll()`.
- `CGI.md` – CGI execution flow, process isolation, and pipe-based communication.

Each file is designed to be a clean reference for the corresponding subsystem.

## How to use

- Read `HTTP.md` for the project’s HTTP protocol handling and routing logic.
- Read `Event-Loop.md` for how the server manages concurrent connections in a single thread.
- Read `CGI.md` for how dynamic Python scripts are executed safely and returned to the client.
