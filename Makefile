# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 14:53:22 by srouhe            #+#    #+#              #
#    Updated: 2019/11/07 11:25:41 by srouhe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

FLAGS = -Wall -Werror -Wextra

SRCS = 	main.c\
		solver.c\
		block.c\
		reader.c

LIBDIR = libft

OBJ = $(patsubst %.c, %.o, $(SRCS))

INCL = .

all: $(NAME)

$(NAME):
	make -C $(LIBDIR)
	clang $(FLAGS) -o $(NAME) $(SRCS) -I $(INCL) -I $(LIBDIR)/includes -L$(LIBDIR) -lft

debug:
	make -C $(LIBDIR)
	clang -g -o $(NAME) $(SRCS) -I $(INCL) -I $(LIBDIR)/includes -L$(LIBDIR) -lft

clean:
	make clean -C $(LIBDIR)
	@/bin/rm -f *.o

fclean: clean
	make fclean -C $(LIBDIR)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
