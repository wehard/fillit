# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 14:53:22 by srouhe            #+#    #+#              #
#    Updated: 2019/11/04 15:06:21 by srouhe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c solver.c

OBJ = $(patsubst %.c, %.o, $(SRCS))

NAME = fillit

HDR = ./

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@clang -I libft/includes -c $(SRCS)
	@clang -o $(NAME) $(OBJ) -I libft/includes -L libft/ -lft

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re
