#!/bin/bash

# Give MariaDB some time to fully initialise and start listening
sleep 10

# Check if WordPress is already installed (to avoid overwriting data)
if [ ! -f /var/www/html/wp-config.php ]; then

	# Download the core WordPress files
	wp core download --allow-root

		# Create the wp-config.php file using variables from the .env file
		# Note: 'mariadb' is the hostname of the database container
		wp config create \
			--dbname="${SQL_DATABASE}" \
			--dbuser="${SQL_USER}" \
			--dbpass="${SQL_PASSWORD}" \
			--dbhost="mariadb:3306" \
			--allow-root

		 # Run the main WordPress installation
		wp core install \
			--url="${DOMAIN_NAME}" \
			--title="${WP_TITLE}" \
			--admin_user="${WP_ADMIN_USER}" \
			--admin_password="${WP_ADMIN_PASSWORD}" \
			--admin_email="${WP_ADMIN_EMAIL}" \
			--allow-root

		# Create a 2nd user (mandatory requirement of the subject)
		wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
			--user_pass="${WP_USER_PASSWORD}" \
			--role=author \
			--allow-root

fi

# Log message for the container log
echo "WordPress setup completed. Starting PHP-FPM..."

# Start PHP-FPM in the foreground (-F). No 'tail -f' or 'sleep infinity' allowed
exec /usr/sbin/php-fpm7.4 -F