#!/bin/bash

# 1. Initialise the system database if it doesn't exist yet
if [ ! -d "/var/lib/mysql/mysql" ]; then
	echo "Initialising MariaDB system tables..."
	mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# 2. Start MariaDB in the background to configure it
# Use '&' to run it while we execute configuration commands.
mysqld_safe --datadir=/var/lib/mysql &

# 3. CRITICAL: Wait for the database to actually start
# This fixes the "Can't connect to local MySQL server through socket" error.
until mysqladmin ping >/dev/null 2>&1; do
	echo "Waiting for MariaDB to wake up..."
	sleep 2
done

# 4. Configure the database using variables from the .env file
# Create the DB and the user that WordPress will use.
mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"
# Note: User is created with '%' to allow connections from other containers
mysql -u root -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mysql -u root -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%';"

# 5. Secure the root user (The Administrator)
# Set a password for root and disable remote root login for security.
mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
mysql -u root -p${SQL_ROOT_PASSWORD} -e "FLUSH PRIVILEGES;"

# 6. Shut down the temporary background service
# Need to stop it so we can restart it as the main process.
mysqladmin -u root -p${SQL_ROOT_PASSWORD} shutdown

# 7. Start MariaDB in the foreground as PID 1
# This is mandatory: no infinite loops, no tail -f hacks.
echo "MariaDB is ready to serve connections"
exec mysqld_safe --datadir=/var/lib/mysql