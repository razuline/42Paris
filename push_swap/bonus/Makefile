# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 17:50:49 by erazumov          #+#    #+#              #
#    Updated: 2025/03/10 18:15:19 by erazumov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker
CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = libft/
FT_PRINTF_DIR = ft_printf/
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRCS = main.c \
		parse_args.c \
		make_instructions.c \
		instructions.c \
		utils.c \
		print_stack.c \
		checker.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader

.PHONY: all clean fclean re norm
