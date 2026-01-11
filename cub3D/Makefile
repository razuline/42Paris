# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 18:41:21 by erazumov          #+#    #+#              #
#    Updated: 2026/01/10 15:37:49 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- EXECUTABLE ---
NAME		=	cub3D

# --- COMPILER AND FLAGS ---
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -Wno-deprecated-declarations
RM			=	rm -rf

# --- DIRS ---
SRC_DIR		=	srcs
OBJ_DIR		=	objs
LIBFT_DIR	=	libft
MLX_DIR		=	mlx
INC_DIR		=	includes

# --- INCLUDES ---
INCLUDES	=	-I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

# --- LIBS ---
LIBFT_DIR	=	libft
MLX_DIR		=	mlx
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx.a

# --- FILES ---
SRC_FILES	=	main.c \
				parsing/init.c \
				parsing/parser.c \
				parsing/parse_map.c \
				parsing/parse_texture.c \
				parsing/parse_color.c \
				parsing/parse_utils.c \
				parsing/valid_map.c \
				parsing/map_utils.c \
				parsing/valid_players.c \
				parsing/flood_fill.c \
				parsing/cleanup.c \
				rendering/render.c \
				rendering/textures.c \
				rendering/player.c \
				rendering/draw.c \
				rendering/utils.c \
				rendering/mlx_utils.c \
				rendering/raycast.c \
				rendering/raycast_utils.c \
				rendering/set_angle.c \
				rendering/set_position.c \
				rendering/init_mlx.c \
				rendering/draw_wall.c \
				rendering/close_game.c

# --- PATHS ---
SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx.a

# --- OS FLAGS ---
OS			=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(OS), Darwin)
	MLXFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error "Unsupported OS: $(OS)")
endif
LDFLAGS		=	-L$(LIBFT_DIR) -lft $(MLXFLAGS)

# --- COLORS ---
RESET		=	\033[0m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
CYAN		=	\033[0;36m
BOLD_GREEN	=	\033[1;32m
BOLD_CYAN	=	\033[1;36m
BOLD_BLUE	=	\033[1;34m

# --- RULES ---
all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			@echo "$(BOLD_CYAN)🔗 Linking $(NAME)...$(RESET)"
			@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
			@echo "$(BOLD_GREEN)✅ $(NAME) ready!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			@echo "$(YELLOW)🪄  Compiling: $<$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
			@echo "$(CYAN)📘 Building Libft...$(RESET)"
			@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

$(MLX):
			@echo "$(CYAN)📘 Building MiniLibX...$(RESET)"
			@make -s -C $(MLX_DIR) > /dev/null 2>&1

clean:
			@echo "$(RED)🧹 Cleaning objects...$(RESET)"
			@$(RM) $(OBJ_DIR)
			-@make clean -s -C $(LIBFT_DIR) > /dev/null 2>&1
			-@make clean -s -C $(MLX_DIR) > /dev/null 2>&1

fclean:		clean
			@echo "$(RED)🗑️  Removing executable...$(RESET)"
			@$(RM) $(NAME)
			@make fclean -s -C $(LIBFT_DIR) > /dev/null 2>&1

re:			fclean all

norm:
			@norminette $(SRC_DIR) $(INC_DIR) | grep -v "OK"
					|| echo "$(GREEN)✅ Norminette OK!$(RESET)"

.PHONY:		all clean fclean re norm

# valgrind --leak-check=full ./cub3D
# leaks --atExit -- ./cub3D ./maps/mini.cub