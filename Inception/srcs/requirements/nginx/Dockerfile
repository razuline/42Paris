# Use the penultimate stable version of Debian
FROM debian:bullseye

	# Install NGINX and OpenSSL, then clean up to save space
	RUN apt-get update && \
		apt-get install -y nginx openssl && \
		rm -rf /var/lib/apt/lists/*

	# Create directory for SSL certificates
	RUN mkdir -p /etc/nginx/ssl

	# Generate a self-signed SSL certificate (no passwords allowed!)
	RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt \
		-keyout /etc/nginx/ssl/inception.key \
		-subj "/C=FR/ST=Paris/L=Paris/O=42/OU=42/CN=vshchere.42.fr"

	# Copy our custom configuration to the container
	COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

	# Port 443 for HTTPS (only entry point allowed)
	EXPOSE 443

	# Start NGINX in the foreground to keep the container running
	CMD ["nginx", "-g", "daemon off;"]