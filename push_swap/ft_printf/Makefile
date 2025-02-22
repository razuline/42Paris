# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 13:50:28 by erazumov          #+#    #+#              #
#    Updated: 2024/12/03 14:44:35 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror
HEADER = ft_printf.h
LIBC = ar rcs
FUNC = $(shell find -name \*.c)
OBJS = $(FUNC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm: norminette -R CheckForbiddenSourceHeader

.PHONY: all clean fclean re
