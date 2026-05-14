# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:17:52 by erazumov          #+#    #+#              #
#    Updated: 2026/05/01 17:17:24 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = webserv

CC         = c++
FLAGS      = -Wall -Wextra -Werror -std=c++98 -g3
INC        = -I includes

SRC_FILES  = main.cpp \
			 Cluster.cpp \
			 Server.cpp \
			 Request.cpp \
			 Response.cpp \
			 Config.cpp \
			 Utils.cpp

SRCS       = $(addprefix srcs/, $(SRC_FILES))

OBJ_DIR    = objs
OBJS       = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

# Colors
Y = \033[33m
R = \033[31m
G = \033[32m
B = \033[34m
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

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
	@echo "$(R)🗑️  Executables removed$(X)"

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full ./webserv
# leaks --atExit -- ./webserv

# http://localhost:8080
# http://localhost:4242
# or
# curl -v http://localhost:8080
# or
# nc localhost 8080