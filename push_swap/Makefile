# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 15:13:07 by erazumov          #+#    #+#              #
#    Updated: 2025/04/10 17:53:03 by erazumov         ###   ########.fr        #
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
		stack/init_stack.c stack/push_pop.c stack/utils.c  \
			stack/utils_2.c \
		operations/swap.c operations/push.c operations/rotate.c \
			operations/reverse_rotate.c \
		sort/small_sort.c sort/turk_sort.c sort/sort_utils.c \
			parcing/parce_args.c parcing/parce_utils.c
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

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
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Object files removed$(RESET)"


fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)🗑️  Executables removed$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
