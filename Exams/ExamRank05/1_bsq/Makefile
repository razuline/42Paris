# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/18 13:40:25 by erazumov          #+#    #+#              #
#    Updated: 2026/04/18 17:02:42 by erazumov         ###   ########.fr        #
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

clean_tests:
	@rm -f test*.txt error*.txt map.txt test_performance_100x100.txt
	@echo "$(R)🗑️  Test files removed$(X)"

fclean: clean clean_tests
	@rm -f $(NAME)
	@echo "$(R)🗑️  Executables removed [$(NAME)]$(X)"

re: fclean all

.PHONY: all clean fclean re clean_tests

# ./bsq map.txt
# valgrind ./bsq map.txt
# cat map.txt | ./bsq