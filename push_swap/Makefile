# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 15:13:07 by erazumov          #+#    #+#              #
#    Updated: 2025/03/05 11:39:10 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

SRCS_DIR = srcs/
OBJS = $(SRCS_DIR:.c=.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf/
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME) $(LIBFT) $(FT_PRINTF)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
