# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 13:03:55 by erazumov          #+#    #+#              #
#    Updated: 2025/04/12 17:02:48 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes/
LIBC = ar rcs

SRC_DIR = src/
OBJ_DIR = obj/

LIBFT_SRC = ft_lib/ft_isalpha.c ft_lib/ft_isdigit.c ft_lib/ft_isalnum.c \
		ft_lib/ft_isascii.c ft_lib/ft_isspace.c ft_lib/ft_isprint.c \
		ft_lib/ft_strlen.c ft_lib/ft_memset.c ft_lib/ft_bzero.c \
		ft_lib/ft_memcpy.c ft_lib/ft_memmove.c ft_lib/ft_strlcpy.c \
		ft_lib/ft_strlcat.c \
		ft_lib/ft_toupper.c ft_lib/ft_tolower.c ft_lib/ft_strchr.c \
		ft_lib/ft_strrchr.c ft_lib/ft_strncmp.c ft_lib/ft_memchr.c \
		ft_lib/ft_memcmp.c ft_lib/ft_strnstr.c ft_lib/ft_atoi.c \
		ft_lib/ft_calloc.c ft_lib/ft_strdup.c ft_lib/ft_substr.c \
		ft_lib/ft_strjoin.c ft_lib/ft_strtrim.c ft_lib/ft_split.c \
		ft_lib/ft_itoa.c ft_lib/ft_strmapi.c ft_lib/ft_striteri.c \
		ft_lib/ft_putchar_fd.c ft_lib/ft_putstr_fd.c ft_lib/ft_putendl_fd.c \
		ft_lib/ft_putnbr_fd.c ft_lib/ft_atol.c
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_formats.c \
		ft_printf/ft_printstr.c ft_printf/ft_printnbr.c \
		ft_printf/ft_printchar.c ft_printf/ft_printhex.c ft_printf/ft_printptr.c \
		ft_printf/ft_print_u.c

SRC = $(LIBFT_SRC) $(PRINTF_SRC)
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
