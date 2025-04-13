# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 18:21:02 by erazumov          #+#    #+#              #
#    Updated: 2025/04/13 19:30:22 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = push_swap

# Compiler and flags
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/
INCLUDES = -I includes/

# Libft specifics
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)/includes

# Source Files
SRC = main.c \
		swap.c \
		push.c \
		rotate.c \
		rev_rotate.c \
		parse.c \
		sort_small.c \
		sort_large.c \
		utils.c \
		stack_utils.c \
		move_utils.c \
		find_utils.c \
		idx_utils.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Colors
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m

# Rules
all: $(NAME)

$(LIBFT_A):
	@echo "$(BLUE)📘 Building Libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful ➜ $(NAME)$(RESET)"

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)📁 Created object directory: $(OBJ_DIR)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) -c $< -o $@
	@echo "$(YELLOW)🪄 Compiling:$(RESET) $< -> $@"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Object files removed$(RESET)"
	
fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(RED)🗑️ Executables removed$(RESET)"
	@echo "$(RED)🗑️ Libft cleaned$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
