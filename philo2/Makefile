# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 10:29:29 by erazumov          #+#    #+#              #
#    Updated: 2025/06/16 18:41:43 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
INCLUDE = -I

HFILES = philo.h

CFILES = main.c \
		 init.c \
		 simulation.c \
		 actions.c \
		 cleanup.c \
		 utils.c

OBJECTS = $(CFILES:.c=.o)

# Colors
Y = \033[33m
R = \033[31m
G = \033[32m
B = \033[34m
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

%.o : %.c
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJECTS)
	@echo "$(Y)📁 Compiling object files [$(NAME)]...$(X)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(G)✅ Finished [$(NAME)]$(X)"

clean:
	@rm -f $(OBJECTS)
	@echo "$(R)🧹 Object files removed [$(OBJECTS)]$(X)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)🗑️  Executables removed [$(NAME)]$(X)"

re: fclean all

norm:
	@norminette $(HFILES) $(CFILES) | grep -v "OK" || true

.PHONY: all clean fclean re norm
