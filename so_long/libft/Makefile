# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 13:03:55 by erazumov          #+#    #+#              #
#    Updated: 2025/04/19 17:06:02 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -fPIC
INCLUDE = -I includes/
LIBC = ar rcs

SRC_DIR = src/
OBJ_DIR = obj/

LIBFT_SRC = lib/ft_isalpha.c lib/ft_isdigit.c lib/ft_isalnum.c \
		lib/ft_isascii.c lib/ft_isspace.c lib/ft_isprint.c \
		lib/ft_strlen.c lib/ft_memset.c lib/ft_bzero.c \
		lib/ft_memcpy.c lib/ft_memmove.c lib/ft_strlcpy.c \
		lib/ft_strlcat.c lib/ft_strcmp.c \
		lib/ft_toupper.c lib/ft_tolower.c lib/ft_strchr.c \
		lib/ft_strrchr.c lib/ft_strncmp.c lib/ft_memchr.c \
		lib/ft_memcmp.c lib/ft_strnstr.c lib/ft_atoi.c \
		lib/ft_calloc.c lib/ft_strdup.c lib/ft_substr.c \
		lib/ft_strjoin.c lib/ft_strtrim.c lib/ft_split.c \
		lib/ft_itoa.c lib/ft_strmapi.c lib/ft_striteri.c \
		lib/ft_putchar_fd.c lib/ft_putstr_fd.c lib/ft_putendl_fd.c \
		lib/ft_putnbr_fd.c lib/ft_atol.c lib/free_split_result.c
PRINTF_SRC = printf/ft_printf.c printf/ft_formats.c \
		printf/ft_printstr.c printf/ft_printnbr.c \
		printf/ft_printchar.c printf/ft_printhex.c printf/ft_printptr.c \
		printf/ft_print_u.c
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c

SRC = $(LIBFT_SRC) $(PRINTF_SRC) $(GNL_SRC)
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)
	@echo "Compilation successful ➜ $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
