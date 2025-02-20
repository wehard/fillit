# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 14:53:22 by srouhe            #+#    #+#              #
#    Updated: 2019/11/07 13:58:14 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

FLAGS = -Wall -Werror -Wextra

SRCS = 	main.c\
		solver.c\
		block.c\
		reader.c

LIBDIR = libft

INCL = .

all: $(NAME)

$(NAME):
	@make -C $(LIBDIR)
	@clang $(FLAGS) -o $(NAME) $(SRCS) -I $(INCL) -I $(LIBDIR)/includes -L$(LIBDIR) -lft

clean:
	@make clean -C $(LIBDIR)
	@/bin/rm -f *.o

fclean: clean
	@make fclean -C $(LIBDIR)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
