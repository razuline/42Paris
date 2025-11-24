# 42 HEADER

NAME	= rush02

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.c \
		  utils.c \
		  # Other functions

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
