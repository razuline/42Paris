# Base image
FROM			debian:bullseye

	# Install necessary dependencies:
	# php-fpm (the translator), php-mysql (database bridge),
	# curl (to download files).
	RUN			apt-get update && apt-get install -y \
				php7.4-fpm \
				php7.4-mysql \
				mariadb-client \
				curl \
				&& rm -rf /var/lib/apt/lists/*

	# Download and install WP-CLI (WordPress Command Line Interface)
	# This tool allows us to configure WordPress without a browser
	RUN			curl -O https://raw.githubusercontent.com/wp-cli/builds \
							/gh-pages/phar/wp-cli.phar \
				&& chmod +x wp-cli.phar \
				&& mv wp-cli.phar /usr/local/bin/wp

	# Prepare directories for PHP-FPM socket and WordPress files
	RUN			mkdir -p /var/www/html
	RUN			mkdir -p /run/php

	# Copy the custom PHP-FPM configuration
	COPY		conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

	# Copy the initialisation script and set execution permission
	COPY		tools/wp_setup.sh /usr/local/bin/wp_setup.sh
	RUN			chmod +x /usr/local/bin/wp_setup.sh

	# Set the working directory to where WordPress will be installed
	WORKDIR		/var/www/html

	# Port 9000 is the default for communication between NGINX and PHP-FPM
	EXPOSE		9000

	# Execute the setup script when the container starts
	ENTRYPOINT	[ "/usr/local/bin/wp_setup.sh" ]
