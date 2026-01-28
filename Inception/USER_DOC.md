# 📖 User Documentation (USER_DOC.md)

This document provides instructions on how to manage and interact with the **Inception** infrastructure.

## 🟢 Services Provided
The stack provides the following interconnected services:
* **NGINX**: A secure web server acting as the sole entry point via port 443 using TLSv1.2/v1.3.
* **WordPress**: A dynamic content management system powered by PHP-FPM.
* **MariaDB**: A robust relational database management system that stores all website content.

## ⚙️ Managing the Project
Use the provided `Makefile` at the root of the repository to manage the lifecycle of the project:
* **Start**: Run `make` to build images and launch containers.
* **Stop**: Run `make down` to stop all running services.
* **Full Reset**: Run `make fclean` to stop services and delete all persistent data.

## 🌐 Accessing the Site
* **Main Website**: Open your browser and go to `https://erazumov.42.fr`.
* **Admin Panel**: Access the WordPress dashboard at `https://erazumov.42.fr/wp-admin` to manage posts and users.

## 🔑 Credentials and Security
* All sensitive information (passwords, usernames, database names) is stored in the `srcs/.env` file.
* **Note**: These credentials are never stored in the source code or images for security reasons.

## ✅ Health Check
To ensure services are running correctly:
1. Run `docker-compose -f srcs/docker-compose.yml ps` in the terminal.
2. All containers (`nginx`, `wordpress`, `mariadb`) should be in the **Up** or **Running** state.