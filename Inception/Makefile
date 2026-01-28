# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 21:39:21 by erazumov          #+#    #+#              #
#    Updated: 2026/01/28 16:43:02 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
# 42 login is used for volume paths and domain configuration
LOGIN = erazumov
# Path where the persistent data will be stored on the host machine
DATA_PATH = /home/$(LOGIN)/data

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Defaul rule: starts the whole infrastructure
all: up

# 1. Create necessary directories on the host
# 2. Build and start the containers in detached mode
up:
	@echo "$(GREEN)Creating data directories...$(RESET)"
	@mkdir -p $(DATA_PATH)/mariadb
	@mkdir -p $(DATA_PATH)/wordpress
	@echo "$(GREEN)Starting containers...$(RESET)"
	@docker-compose -f srcs/docker-compose.yml up --build -d

# Stop all running containers
down:
	@echo "$(RED)Stopping containers...$(RESET)"
	@docker-compose -f srcs/docker-compose.yml down

# Stop and remove containers, networks, and images created by 'up'
clean: down
	@echo "$(RED)Cleaning up...$(RESET)"
	@docker system prune -a --force

# Full cleanup: removes everything including VOLUMES
# WARNING: This will delete the database and website files!
fclean: clean
	@echo "$(RED)Removing volumes and data directories...$(RESET)"
	@docker volume rm $$(docker volume ls -q) || true
	@sudo rm -rf $(DATA_PATH)

# Rebuild the entire project from scratch
re: fclean all

# Utility command to view container status
status:
	@docker-compose -f srcs/docker-compose.yml ps

# Utility command to view real-time logs
logs:
	@docker-compose -f srcs/docker-compose.yml logs -f

.PHONY: all up down clean fclean re
