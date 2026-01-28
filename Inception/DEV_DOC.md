# 🛠 Developer Documentation (DEV_DOC.md)

This guide explains the technical setup, configuration, and management of the **Inception** development environment.

## 🛠 Prerequisites & Setup
To set up the environment from scratch:
1. **Operating System**: A Virtual Machine running Debian or a compatible Linux/macOS environment.
2. **Environment Variables**: Create a `srcs/.env` file based on the project requirements to store database and WordPress secrets.
3. **Hosts Configuration**: Add `127.0.0.1 erazumov.42.fr` to your `/etc/hosts` file.

## 🏗 Build and Launch
The project uses **Docker Compose** for orchestration:
* **Build Command**: `make` (triggers `docker-compose up --build`).
* **Images**: Custom-built from Dockerfiles located in `srcs/requirements/`.

## 👨‍💻 Management Commands
Use these commands to manage containers and debug:
* **View Logs**: `docker-compose logs -f [service_name]`
* **Execute Shell**: `docker exec -it [container_name] bash`
* **Clean System**: `docker system prune -a`

## 💾 Data Persistence
* **Storage Location**: Data persists on the host machine at `/home/erazumov/data/`.
* **Volumes**: We use **Docker Named Volumes** (`mariadb_data` and `wordpress_data`) for persistent storage.
* **Implementation**: Managed via the `volumes` section in `docker-compose.yml` using the `local` driver and `bind` options.