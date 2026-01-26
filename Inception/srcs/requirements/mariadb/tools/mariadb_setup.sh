#!/bin/bash

# 1. Start MariaDB service temporarily to configure it
service mariadb start;

# 2. Create the database if it doesn't exist
#	 Use variables defined in the .env file
mariadb -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"

# 3.Create a user and set a password for them
# Note: The username must NOT be 'admin' or 'administrator'
mariadb -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'localhost' \
			IDENTIFIED BY '${SQL_PASSWORD}';"

# 4. Grant all privileges to this user on the new database
mariadb -e "GRANT ALL PRIVILEGES ON \`{SQL_DATABASE}\`.* \
			TO \`{SQL_USER}\`@'%'
			IDENTIFIED BY '${SQL_PASSWORD}';"

# 5. Set the password for the root user (administrator)
#	 Root is the most powerful user, so this password must be secure
mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"

# 6. Apply changes immediately
mariadb -e "FLUSH PRIVILEGES;"

# 7. Shutdown the temporary service safely
mysqladmin -u root -p "${SQL_ROOT_PASSWORD}" shutdown

# 8. Start MariaDB in the foreground (as the main process)
#	 This keeps the container alive and is required by Docker best practices
exec mysqld_safe