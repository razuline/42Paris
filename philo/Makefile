# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 10:29:29 by erazumov          #+#    #+#              #
#    Updated: 2025/06/07 17:10:01 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDE = -I include/

SRC_DIR = src/
SRC = main.c init.c philo.c monitor.c utils.c time_utils.c cleanup.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Colors
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful ➜ $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)📁 Created object directory: $(OBJ_DIR)$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🗑️  Executables removed$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
