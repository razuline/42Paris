# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/02 13:06:15 by erazumov          #+#    #+#              #
#    Updated: 2026/01/17 13:32:56 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = AForm

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp \
	   Bureaucrat.cpp \
	   AForm.cpp \
	   ShrubberyCreationForm.cpp \
	   RobotomyRequestForm.cpp \
	   PresidentialPardonForm.cpp

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
	@rm -f *_shrubbery
	@echo "$(R)🗑️  Executables and files removed [$(NAME)]$(X)"

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full ./AForm