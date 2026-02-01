# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 21:39:21 by erazumov          #+#    #+#              #
#    Updated: 2026/02/01 14:36:32 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
# Login is used for volume paths and domain configuration
LOGIN = razuline
LOGIN_42 = erazumov

# Detect Operating System
UNAME_S = $(shell uname -s)

# Set DATA_PATH based on the OS
# On macOS (Darwin), use the /Users/ path
# On Linux (Evaluation VM), use the mandatory /home/ path
ifeq ($(UNAME_S), Darwin)
	DATA_PATH = /Users/$(LOGIN)/data
else
	DATA_PATH = /home/$(LOGIN_42)/data
endif

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default rule: starts the whole infrastructure
all: up

# 1. Create necessary directories on the host
# 2. Build and start the containers in detached mode
up:
	@echo "$(GREEN)Detected OS: $(UNAME_S)$(RESET)"
	@echo "$(GREEN)Using DATA_PATH: $(DATA_PATH)$(RESET)"
	@mkdir -p $(DATA_PATH)/mariadb
	@mkdir -p $(DATA_PATH)/wordpress
	DATA_PATH=$(DATA_PATH) docker compose -f srcs/docker-compose.yml up --build -d

# Stop all running containers
down:
	@echo "$(RED)Stopping containers...$(RESET)"
	@docker compose -f srcs/docker-compose.yml down

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
	@docker compose -f srcs/docker-compose.yml ps

# Utility command to view real-time logs
logs:
	@docker compose -f srcs/docker-compose.yml logs -f

.PHONY: all up down clean fclean re
