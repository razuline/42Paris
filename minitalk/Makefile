# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 11:19:09 by erazumov          #+#    #+#              #
#    Updated: 2025/02/16 16:08:29 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
SERVER = server
CLIENT = client
PRINTF = libftprintf.a

CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes/

SERVER_FILES = server.c
CLIENT_FILES = client.c

SRC_DIR = src/
SERVER_SRC = $(addprefix $(SRC_DIR), $(SERVER_FILES))
CLIENT_SRC = $(addprefix $(SRC_DIR), $(CLIENT_FILES))

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVER) $(CLIENT) $(PRINTF)

$(SERVER): $(SERVER_OBJ)
	@make -C ft_printf/
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(INCLUDE) ft_printf/$(PRINTF) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
	@make -C ft_printf/
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(INCLUDE) ft_printf/$(PRINTF) -o $(CLIENT)

clean:
	@make clean -C ft_printf/
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	@make fclean -C ft_printf/
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
