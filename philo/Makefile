# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 10:29:29 by erazumov          #+#    #+#              #
#    Updated: 2025/04/07 11:30:48 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c src/init.c src/time.c src/actions.c src/forks.c \
		src/simulation.c src/monitor.c src/utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: norminette -R CheckForbiddenSourceHeader

.PHONY: all clean fclean re norm
