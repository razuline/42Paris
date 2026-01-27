*This project has been created as part of the 42 curriculum by erazumov.*

# Inception - System Administrator & Docker

## 📌 Project Overview
This project consists of virtualising a small infrastructure using **Docker Compose**. The entire stack runs on **Debian Bullseye**, with each service isolated in its own dedicated container.

The goal is to build a secure, interconnected environmental for a WordPress site, ensuring high security and proper data persistence.

### 🏗️ Design Choices & Comparisons
In accordance with the project requirements, here is a comparison of the technologies used:
* **Virtual Machines vs Docker**: While VMs virtualise hardware, Docker virtualises the OS kernel. Docker is much more lightweight, faster to start, and consumes fewer resources.
* **Secrets vs Environment Variables**: Environment variables (via `.env`) are great for general configuration. However, **Docker Secrets** are more secure for passwords because they are encrypted at rest and never stored in the image itself.
* **Docker Network vs Host Network**: We use a private **Docker bridge network** to isolate services. Unlike the "host" network, this prevents external access to MariaDB and WordPress, allowing only NGINX to be the entry point.
* **Docker Volumes vs Bind Mounts**: We use **Named Volumes** stored in `/home/vshchere/data`. Unlike bind mounts, named volumes are managed by Docker, providing better performance and security for persistent data.

### ⚙️ Architecture
The infrastructure follows a microservices-based approach:
* **NGINX:** The only entry point (Port 443, TLSv1.2/v1.3 only).
* **WordPress + PHP-FPM:** The core application logic, (Port 9000).
* **MariaDB:** Database engine (Port 3306).

### 🔄 Service Interaction
1. **NGINX** receives an HTTPS request from the browser.
2. If the request is for a `.php` file, it is forwarded to **WordPress (PHP-FPM)** via the FastCGI protocol.
3. **WordPress** processes the logic and queries **MariaDB** for content if data is needed.
4. The result is sent back through NGINX to the user's browser as a standard HTML page.

---

## 🛠️ Instructions (Installation & Execution)
To set up the environment, follow these steps:
1. **Configure Domain**:
	Update your `/etc/hosts` to point the domain to your local IP.

	```bash
	echo "127.0.0.1 erazumov.42.fr" | sudo tee -a /etc/hosts
	```
2. **Build and Run**:
	Use the provided **Makefile** at the root of the project.

	```bash
	make        # Builds images and starts containers
	make down   # Stops services
	make clean  # Full cleanup of containers and data
	```

---

## 📚 Resources & AI Usage
### References
* [Docker Documentation](https://docs.docker.com/)
* [NGINX TLS Configuration Guide](https://nginx.org/en/docs/http/configuring_https_servers.html)
* [MariaDB Server Administration](https://mariadb.com/kb/en/documentation/)

### AI Assistance Disclosure
* **Tool:** Gemini (AI Collaborator).
* **Usage:** AI was used to help debug the Bash scripts and structure the `.md` files.
* **Validation:** Every AI-generated line was manually reviewed, tested with `bash -n`, and cross-checked with official documentation to ensure full understanding and responsibility.

---

## 📈 Implementation Progress (Roadmap)

### Stage 1: Infrastructure & Security ✅
- [x] Defined the project directory structure according to the subject requirements.
- [x] Configured `.gitignore` to prevent sensitive data leaks.
- [x] Created a secure `.env` file to manage credentials via environment variables.

### Stage 2: NGINX & MariaDB Setup ✅
- [x] Built NGINX with SSL/TLS 1.2/1.3 support.
- [x] Configured MariaDB with automated initialisation via `mariadb_setup.sh`.
- [x] Ensured database persistence using **Docker Volumes** (avoiding "goldfish memory").

### Stage 3: WordPress & PHP-FPM ✅
- [x] Configured PHP-FPM to listen on port 9000.
- [x] Integrated WP-CLI for automated site installation.
- [x] Created an initialisation script to setup the site and users automatically.

### Stage 4: Orchestration & Automation ⚙️
- [ ] Defined service interconnectivity in `docker-compose.yml`.
- [ ] Created a `Makefile` for one-command deployment.
- [ ] Final testing of data persistence and network isolation.

---

## How to Run
1. Update the `/etc/hosts` file:

```bash
echo "127.0.0.1 login.42.fr" | sudo tee -a /etc/hosts
```

2. Build and launch the infrastructure:

```bash
make
```

---

## 🔒 Security Policy
* **No Hardcoded Secrets**: All credentials are managed via the `.env` file (excluded from Git).
* **Network Isolation**: Only NGINX is exposed to the host. Other services communicate over a private bridge network.
* **Modern Encryption**: SSL/TLS protocols are strictly limited to secure versions (1.2 and 1.3).

---

## 💻 Cross-Platform Compatibility
The entire environment has been tested for portability:
* **Linux**: Native performance using the host kernel.
* **macOS**: Runs via a lightweight virtualisation layer, ensuring the same Debian-based environment as the final evaluation machine.

---

## ✏️ Check the Bash-Scripts
To verify script syntax for `mariadb_setup.sh` and `wp_setup.sh`:

```bash
bash -n srcs/requirements/mariadb/tools/mariadb_setup.sh
bash -n srcs/requirements/wordpress/tools/wp_setup.sh
```