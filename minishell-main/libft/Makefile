# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 13:03:55 by erazumov          #+#    #+#              #
#    Updated: 2025/08/15 14:14:09 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include/
LIBC = ar rcs

SRC_DIR = src/
OBJ_DIR = obj/

LIBFT_SRC = ft_lib/ft_isalpha.c ft_lib/ft_isdigit.c ft_lib/ft_isalnum.c \
		ft_lib/ft_isascii.c ft_lib/ft_isspace.c ft_lib/ft_isprint.c \
		ft_lib/ft_strlen.c ft_lib/ft_memset.c ft_lib/ft_bzero.c \
		ft_lib/ft_memcpy.c ft_lib/ft_memmove.c ft_lib/ft_strlcpy.c \
		ft_lib/ft_strlcat.c ft_lib/ft_free_array.c \
		ft_lib/ft_toupper.c ft_lib/ft_tolower.c ft_lib/ft_strchr.c \
		ft_lib/ft_strrchr.c ft_lib/ft_strncmp.c ft_lib/ft_memchr.c \
		ft_lib/ft_memcmp.c ft_lib/ft_strnstr.c ft_lib/ft_atoi.c \
		ft_lib/ft_calloc.c ft_lib/ft_strdup.c ft_lib/ft_substr.c \
		ft_lib/ft_strjoin.c ft_lib/ft_strtrim.c ft_lib/ft_split.c \
		ft_lib/ft_itoa.c ft_lib/ft_strmapi.c ft_lib/ft_striteri.c \
		ft_lib/ft_putchar_fd.c ft_lib/ft_putstr_fd.c ft_lib/ft_putendl_fd.c \
		ft_lib/ft_putnbr_fd.c ft_lib/ft_strcmp.c ft_lib/ft_str_is_numeric.c \
		ft_lib/ft_lstnew.c ft_lib/ft_lstlast.c ft_lib/ft_lstmap.c \
		ft_lib/ft_lstadd_front.c ft_lib/ft_lstadd_back.c \
		ft_lib/ft_lstiter.c ft_lib/ft_lstclear.c ft_lib/ft_lstdelone.c \
		ft_lib/ft_lstsize.c ft_lib/ft_atoi_strict.c ft_lib/ft_strcat.c \
		ft_lib/ft_strcpy.c
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_formats.c \
		ft_printf/ft_printstr.c ft_printf/ft_printnbr.c \
		ft_printf/ft_printchar.c ft_printf/ft_printhex.c ft_printf/ft_printptr.c \
		ft_printf/ft_print_u.c
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c

SRC = $(LIBFT_SRC) $(PRINTF_SRC) $(GNL_SRC)
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Colors
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)
	@echo "$(GREEN)✅ Compilation successful ➜ $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(YELLOW)🪄 Compiling:$(RESET) $< -> $@"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🗑️  Executables libft removed$(RESET)"

re: fclean all

norm:
	@norminette $(SRC_DIR) include/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
