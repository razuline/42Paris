# Inception - System Administrator & Docker

## 📝 Project Overview
This project consists of virtualising a small infrastructure using **Docker Compose**. The entire stack runs on **Debian Bullseye**, with each service isolated in its own dedicated container.

The goal is to bild a secire, interconnected environmental for a WordPress site, ensuring high seciruty and proper data persistence.

### 🏗️ Architecture
The infrastructure follows a microservices-based approach:
* **NGINX:** The only entry point for the infrastructure. It handles HTTPS requests via **TLSv1.2/v1.3** on port 443.
* **WordPress + PHP-FPM:** The core application logic, listening on port 9000.
* **MariaDB:** The database management system, listening on port 3306.

---

## 🛠️ Implementation Progress (Roadmap)

### Stage 1: Infrastructure & Security ✅
- [x] Defined the project directory structure according to the subject requirements.
- [x] Configured `.gitignore` to prevent sensitive data leaks.
- [x] Created a secure `.env` file to manage credentials via environment variables.

### Stage 2: NGINX & MariaDB Setup ✅

#### NGINX (The Gatekeeper)
- [x] Built the image from `debian:bullseye`.
- [x] Generated a self-signed **SSL Certificate** using OpenSSL.
- [x] Configured the server to support only **TLSv1.2/v1.3** protocols.
- [x] Set up the `nginx.conf` to proxy PHP requests to the WordPress service.

#### MariaDB (The Archive)
- [x] Built the image from `debian:bullseye`.
- [x] Modified `50-server.cnf` to allow network connections (`bind-address = 0.0.0.0`).
- [x] Created a robust `mariadb_setup.sh` script to:
	- Initialise the database and users on the first run.
	- Secure the `root` account with a password from `.env`.
	- Create a non-root user for the WordPress application.
- [x] Ensured the service runs as the main process (`exec mysqld_safe`).

### Stage 3: WordPress & PHP-FPM 📅
- [ ] Install and configure PHP-FPM for Debian.
- [ ] Implement **WP-CLI** for automated WordPress installation and setup.
- [ ] Link the WordPress container to the MariaDB service.

### Stage 4: Orchestration & Automation 📅
- [ ] Define the network and volume mapping in `docker-compose.yml`.
- [ ] Set up **Docker Volumes** for data persistency (avoiding "goldfish memory").
- [ ] Write a `Makefile` to automate the build, run, and clean-up processes.

---

## 🔒 Security Policy
* **No Hardcoded Secrets**: All passwords and sensitive data are stored in `.env` and are strictly excluded from version control via `.gitignore`.
* **Network Isolation**: Only NGINX is exposed to the host machine. MariaDB and WordPress communicate through a private internal Docker network.
* **Modern Encryption**: SSL/TLS protocols are strictly limited to secure versions to prevent vulnerabilities.