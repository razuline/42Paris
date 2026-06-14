# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:17:52 by erazumov          #+#    #+#              #
#    Updated: 2026/06/14 18:34:43 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = webserv

CC         = c++
FLAGS      = -Wall -Wextra -Werror -std=c++98 -Og -g3 #-fsanitize=address,undefined
INC        = -I includes

SRC_FILES  = main.cpp \
			 Cluster.cpp \
			 Server.cpp \
			 Config.cpp \
			 Request.cpp \
			 Response.cpp \
			 Location.cpp \
			 CGI.cpp \
			 Utils.cpp

SRCS       = $(addprefix srcs/, $(SRC_FILES))

OBJ_DIR    = objs
OBJS       = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

TEST_ROOT  = www

# Colors
Y = \033[33m
R = \033[31m
G = \033[32m
B = \033[34m
C = \033[36m
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

test: $(NAME)
	@printf "$(C)[DIR] $(X)  Generating YoupiBanane directory matrix in root...\n"
	@rm -rf YoupiBanane
	@mkdir -p YoupiBanane/nop
	@mkdir -p YoupiBanane/Yeah
	@touch YoupiBanane/youpi.bad_extension
	@touch YoupiBanane/youpi.bla
	@touch YoupiBanane/nop/youpi.bad_extension
	@touch YoupiBanane/nop/other.pouic
	@touch YoupiBanane/Yeah/not_happy.bad_extension
	@printf "$(G)[OK]  $(X)  Root directory matrix deployed.\n"
	@printf "$(Y)[RUN] $(X)  Executing integration tester (Make sure webserv is running!)...\n"
	@if [ -f ./tester ]; then \
		chmod +x ./tester && ./tester http://localhost:8080; \
	elif [ -f $(TEST_ROOT)/test.py ]; then \
		python3 $(TEST_ROOT)/test.py; \
	else \
		printf "$(Y)[WARN]$(X)  No local tester binaries found.\n"; \
	fi

$(NAME): $(OBJS)
	@printf "$(G)[LD]  $(X)  Linking executable target: $(NAME)\n"
	@$(CC) $(FLAGS) $(INC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "$(Y)[CC]  $(X)  Compiling source frame: $<\n"
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@printf "$(UP)$(CUT)"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(R)[RM]  $(X)  Cleaned internal object cache\n"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf YoupiBanane
	@rm -f .server.pid
	@printf "$(R)[RM]  $(X)  Removed compiled binary and generated test directories\n"

re: fclean
	@+$(MAKE) all --jobs=$(shell nproc) --no-print-directory

.PHONY: all clean fclean re test

# valgrind --leak-check=full ./webserv
# leaks --atExit -- ./webserv

# http://localhost:8080
# http://localhost:4242
# or
# curl -v http://localhost:8080
# or
# nc localhost 8080