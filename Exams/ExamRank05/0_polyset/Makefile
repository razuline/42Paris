# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/20 12:57:16 by erazumov          #+#    #+#              #
#    Updated: 2026/05/05 21:13:18 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = polyset

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
INC = -I includes

SRC_FILES = main.cpp \
			array_bag.cpp \
			tree_bag.cpp \
			searchable_array_bag.cpp \
			searchable_tree_bag.cpp \
			set.cpp

SRCS = $(addprefix srcs/, $(SRC_FILES))

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

# Colors
Y = \033[33m
R = \033[31m
G = \033[32m
B = \033[34m
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

$(OBJ_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS)
	@echo "$(Y)📁 Compiling object files [$(NAME)]...$(X)"
	@$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "$(G)✅ Finished [$(NAME)]$(X)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(R)🧹 Object files removed$(X)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)🗑️  Executables removed$(X)"

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full ./polyset
# leaks --atExit -- ./polyset