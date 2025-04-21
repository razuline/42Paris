# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 13:28:17 by erazumov          #+#    #+#              #
#    Updated: 2025/04/21 16:50:41 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = so_long

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR) -lft $(MLXFLAGS) -pie
RM = rm -f
RMDIR = rm -rf

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/
MLX_DIR = mlx/

# Includes
INCLUDES = -I includes/ -I $(MLX_DIR) -I $(LIBFT_DIR)/includes

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = main.c \
	  error.c \
	  init.c \
	  hooks.c \
	  render.c \
	  cleanup.c \
	  game_logic.c \
	  map_reader.c \
	  map_reader_utils.c \
	  map_valid.c \
	  map_valid_utils.c \
	  map_grid_utils.c \
	  path_utils.c \
	  stack_utils.c \
	  valid_path.c \
	  player_move.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# OS Detection and MLX Configuration
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	# Linux configuration
	MLXFLAGS = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm -lbsd
	CFLAGS += -D__linux__
else
	$(error "Unsupported OS: $(OS)")
endif

# Linker flags
LDFLAGS = -L$(LIBFT_DIR) -lft $(MLXFLAGS)

# Colors
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m

# Rules
all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)📘 Building Libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) | $(LIBFT)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(RED)❌ Error: $(MLX_DIR) not found.$(RESET)"; \
		exit 1; \
	fi
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful ➜ $(NAME)$(RESET)"

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)📁 Created object directory: $(OBJ_DIR)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)🪄 Compiling:$(RESET) $< -> $@"

clean:
	$(RMDIR) $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Object files removed$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(RED)🗑️ Executables removed$(RESET)"
	@echo "$(RED)🗑️ Libft cleaned$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
