/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:35:38 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/05 11:27:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
//# include "block.h"

# define BUF_SIZE 21

typedef struct	s_map
{
	int			size;
	uint64_t	map;
}				t_map;

void			solve(t_list *block_list, int n_blocks);
void			print_map(uint64_t map);
void			print_block_list(t_list *block_list, int size);

t_list			*read_blocks(const int fd, int *n_blocks);

#endif
