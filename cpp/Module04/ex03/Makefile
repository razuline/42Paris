# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 16:31:43 by erazumov          #+#    #+#              #
#    Updated: 2025/12/01 14:40:21 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Interfaces

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

SRC_DIR = srcs
OBJ_DIR = objs

SRC_FILES = srcs/main.cpp \
			srcs/AMateria.cpp \
			srcs/Ice.cpp \
			srcs/Cure.cpp \
			#srcs/.cpp

OBJ_NAMES = $(notdir $(SRC_FILES:.c=.o))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

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
	@echo "$(Y)📁 Compiling object files [$(NAME)]...$(X)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) 
	@echo "$(G)✅ Finished [$(NAME)]$(X)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CXX) $(CXXFLAGS) -Iincludes -c $< -o $@
	@printf "$(UP)$(CUT)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(B)📁 Created object directory: $(OBJ_DIR)$(X)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(R)🧹 Object files removed [$(OBJ_DIR)]$(X)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(R)🗑️  Executables removed [$(NAME)]$(X)"

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full ./Polymorphism