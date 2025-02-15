# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 11:19:09 by erazumov          #+#    #+#              #
#    Updated: 2025/02/15 11:47:08 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(shell find $(SRC_DIR) -name \*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SERVER = server
CLIENT = client
SERVER_OBJS = $(OBJ_DIR)/server.o
CLIENT_OBJS = $(OBJ_DIR)/client.o

all: $(SERVER) $(CLIENT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER)
$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re


