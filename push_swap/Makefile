# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 15:13:07 by erazumov          #+#    #+#              #
#    Updated: 2025/04/12 16:11:13 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = push_swap
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes/

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

# Source Files
SRC = main.c \
		operations/swap.c \
		operations/push.c \
		operations/rotate.c \
		operations/reverse_rotate.c \
		parcing/parce.c \
		sort/small_sort.c \
		sort/chunk_sort.c \
		utils/utils.c \
		utils/sort_utils.c \
		utils/parce_utils.c \
		utils/positions.c
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Variables
RM = rm -rf

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful ➜ $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Object files removed$(RESET)"


fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)🗑️  Executables removed$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
