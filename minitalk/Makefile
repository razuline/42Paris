# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 11:19:09 by erazumov          #+#    #+#              #
#    Updated: 2025/04/10 14:04:47 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
SERVER		= server
CLIENT		= client
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I includes/

# Directories
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a

# Source Files
SERVER_SRC	= server.c
CLIENT_SRC	= client.c
SERVER_OBJ	= $(addprefix $(OBJ_DIR)/,$(SERVER_SRC:.c=.o))
CLIENT_OBJ	= $(addprefix $(OBJ_DIR)/,$(CLIENT_SRC:.c=.o))

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

# Rules
all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT) $(SERVER_OBJ)
	@$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)
	@echo "$(GREEN)✅ Server compiled ➜ ./$(SERVER)$(RESET)"

$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)
	@echo "$(GREEN)✅ Client compiled ➜ ./$(CLIENT)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)🧹 Object files removed$(RESET)"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)🗑️  Executables removed$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ $(LIBFT_DIR) | grep -v "OK" || true

.PHONY: all clean fclean re norm
