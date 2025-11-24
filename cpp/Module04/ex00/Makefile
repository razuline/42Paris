# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 16:31:43 by erazumov          #+#    #+#              #
#    Updated: 2025/11/24 13:35:44 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Polymorphism

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp Animal.cpp Cat.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp
OBJS = $(SRCS:.cpp=.o)

# Colors
Y = \033[33m
R = \033[31m
G = \033[32m
B = \033[34m
X = \033[0m
UP = \033[A
CUT = \033[K

all: $(NAME)

%.o: %.cpp
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS)
	@echo "$(Y)📁 Compiling object files [$(NAME)]...$(X)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) 
	@echo "$(G)✅ Finished [$(NAME)]$(X)"

clean:
	@rm -f $(OBJS)
	@echo "$(R)🧹 Object files removed [$(OBJS)]$(X)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)🗑️  Executables removed [$(NAME)]$(X)"

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full ./Polymorphism