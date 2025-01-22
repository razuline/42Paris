# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 12:50:34 by erazumov          #+#    #+#              #
#    Updated: 2025/01/22 13:52:40 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap.a

CFLAGS = -Wall -Wextra -Werror
INCS = ./includes/
LIBC = ar rcs
SRCS = $(shell find -name \*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm: norminette -R CheckForbiddenSourceHeader

.RHONY: all clean fclean re
