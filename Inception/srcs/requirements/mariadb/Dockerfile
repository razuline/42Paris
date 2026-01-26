# 1. Base image
FROM			debian:bullseye

	# 2. Install MariaDB and clean cache to keep image small
	RUN			apt-get update && \
				apt-get install -y mariadb-server && \
				rm -rf /var/lib/apt/lists/*

	# 3. Create necessary directories for MariaDB to run
	#	 MariaDB needs a place to store its process ID file (PID)
	RUN			mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

	# 4. Copy the custom config
	#	 This config will tell MariaDB to listen to the whole network
	COPY		conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

	# 5. Copy and prepare the initialisation script
	#	 This script will creaye the databasse and users on the first run
	COPY		tools/mariadb_setup.sh /usr/local/bin/
	RUN			chmod +x /usr/local/bin/mariadb_setup.sh

	# 6. Expose the default MariaDB port
	EXPOSE		3306

	# 7. Set the entrypoint to the script
	#	 This is where the "magic" of setting up password happens
	ENTRYPOINT	[ "mariadb_setup.sh" ]
