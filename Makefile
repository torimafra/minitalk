NAME_C = client
NAME_S = server

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS_C = $(NAME_C).c utils.c
SRCS_S = $(NAME_S).c utils.c

OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJS_C)
	$(CC) $(CFLAGS) $(OBJS_C) -o $(NAME_C)

$(NAME_S): $(OBJS_S)
	$(CC) $(CFLAGS) $(OBJS_S) -o $(NAME_S)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_C) $(OBJS_S)

fclean: clean
	rm -f $(NAME_C) $(NAME_S)

re: fclean all

.PHONY: all clean fclean re
