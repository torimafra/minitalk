# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 17:20:26 by vimafra-          #+#    #+#              #
#    Updated: 2025/05/22 17:30:22 by vimafra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS_C = $(NAME_C).c utils.c
SRCS_S = $(NAME_S).c itoa.c utils.c

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
