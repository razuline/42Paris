# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 10:29:29 by erazumov          #+#    #+#              #
#    Updated: 2025/06/07 14:22:49 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDE = -I include/

SRC_DIR = src/
SRC = main.c init.c philo.c monitor.c utils.c time_utils.c cleanup.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation successful ➜ $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

norm:
	@norminette $(SRC_DIR) includes/ | grep -v "OK" || true

.PHONY: all clean fclean re norm
