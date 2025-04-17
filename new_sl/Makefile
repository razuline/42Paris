# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 13:28:17 by erazumov          #+#    #+#              #
#    Updated: 2025/04/17 21:23:09 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = so_long

# Compiler and flags
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/
MLX_DIR = mlx/
INCLUDES = -I includes/

# Libft specifics
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)/includes

# Source Files
SRC = main.c \
		error.c \
		init.c \
		hooks.c \
		render.c \
		map_reader.c map_reader_utils.c \
		map_valid.c map_valid_utils.c \
		valid_path.c map_grid_utils.c \
		player_move.c game_logic.c cleanup.c
VPATH = $(SRC_DIR)
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OS = $(shell uname -s)

ifeq ($(OS), Linux)
	MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
else
	$(warning "Unsupported OS detected: $(OS). Using Linux MLX flags.")
	MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

INCFLAGS = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)
LDFLAGS = -L $(LIBFT_DIR) -lft $(MLXFLAGS)

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
