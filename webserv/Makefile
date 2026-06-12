# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:17:52 by erazumov          #+#    #+#              #
#    Updated: 2026/06/12 16:55:52 by erazumov         ###   ########.fr        #
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
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

test: $(NAME) setup_tester
	@echo "$(G)🚀 Running tests...$(X)"
	@echo "$(B)📁 Creating YoupiBanane directory structure...$(X)"
	@mkdir -p $(TEST_ROOT)/YoupiBanane/nop
	@mkdir -p $(TEST_ROOT)/YoupiBanane/Yeah
	@touch $(TEST_ROOT)/YoupiBanane/youpi.bad_extension
	@touch $(TEST_ROOT)/YoupiBanane/youpi.bla
	@touch $(TEST_ROOT)/YoupiBanane/nop/youpi.bad_extension
	@touch $(TEST_ROOT)/YoupiBanane/nop/other.pouic
	@touch $(TEST_ROOT)/YoupiBanane/Yeah/not_happy.bad_extension
	@ln -sf www/YoupiBanane YoupiBanane 2>/dev/null || true
	@echo "$(G)✅ YoupiBanane structure is ready!$(X)"

$(NAME): $(OBJS)
	@echo "$(Y)📁 Compiling object files...$(X)"
	@$(CC) $(FLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "$(G)✅ Finished [$(NAME)]$(X)"

$(OBJ_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(Y)Compiling [$<]...$(X)"
	$(CC) $(FLAGS) $(INC) -c $< -o $@
	@printf "$(UP)$(CUT)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(R)🧹 Object files removed$(X)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(TEST_ROOT)/YoupiBanane
	@rm -f YoupiBanane
	@echo "$(R)🗑️  Executables and test directories removed$(X)"

re: fclean
	+$(MAKE) all --jobs=$(shell nproc)

.PHONY: all clean fclean re test setup_tester

# valgrind --leak-check=full ./webserv
# leaks --atExit -- ./webserv

# http://localhost:8080
# http://localhost:4242
# or
# curl -v http://localhost:8080
# or
# nc localhost 8080