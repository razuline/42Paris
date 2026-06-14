# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:17:52 by erazumov          #+#    #+#              #
#    Updated: 2026/06/14 16:32:31 by erazumov         ###   ########.fr        #
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

test: $(NAME) setup_tester
	@printf "$(C)[TEST]$(X)  Setting up evaluation testing environment...\n"
	@mkdir -p $(TEST_ROOT)/YoupiBanane/nop
	@mkdir -p $(TEST_ROOT)/YoupiBanane/Yeah
	@touch $(TEST_ROOT)/YoupiBanane/youpi.bad_extension
	@touch $(TEST_ROOT)/YoupiBanane/youpi.bla
	@touch $(TEST_ROOT)/YoupiBanane/nop/youpi.bad_extension
	@touch $(TEST_ROOT)/YoupiBanane/nop/other.pouic
	@touch $(TEST_ROOT)/YoupiBanane/Yeah/not_happy.bad_extension
	@ln -sf www/YoupiBanane YoupiBanane 2>/dev/null || true
	@printf "$(G)[OK]  $(X)  YoupiBanane directory matrix is ready!\n"

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
	@rm -rf $(TEST_ROOT)/YoupiBanane
	@rm -f YoupiBanane
	@printf "$(R)[RM]  $(X)  Removed compiled binary and test roots\n"

re: fclean
	@+$(MAKE) all --jobs=$(shell nproc) --no-print-directory

.PHONY: all clean fclean re test setup_tester

# valgrind --leak-check=full ./webserv
# leaks --atExit -- ./webserv

# http://localhost:8080
# http://localhost:4242
# or
# curl -v http://localhost:8080
# or
# nc localhost 8080