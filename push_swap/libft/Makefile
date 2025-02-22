# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 13:03:55 by erazumov          #+#    #+#              #
#    Updated: 2024/11/24 14:06:33 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
HEADER = libft.h
LIBC = ar rcs
FUNC = $(shell find -name \*.c)
OBJS = $(FUNC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: norminette -R CheckForbiddenSourceHeader

.PHONY: all clean fclean re
