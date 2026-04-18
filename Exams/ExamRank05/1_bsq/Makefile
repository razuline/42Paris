# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/18 13:40:25 by erazumov          #+#    #+#              #
#    Updated: 2026/04/18 13:41:08 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I

HFILES = bsq.h

CFILES = main.c \
		 parsing.c \
		 algo.c \
		 display.c

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