/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:35:38 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/07 13:32:36 by srouhe           ###   ########.fr       */
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

# define BUF_SIZE 21
# define TRUE 1
# define FALSE 0

typedef struct			s_block
{
	char				id;
	uint64_t			bits;
	uint64_t			pos;
}						t_block;

extern	uint64_t		g_valid_blocks[19];
extern	uint64_t		g_map_configs[7];

int						solve(t_list *b_lst, uint64_t map, int *params, int i);
void					print_binary_map(uint64_t map);
void					print_map(char *map, int size, int p);
void					print_b_lst(t_list *b_lst, int nb, int size, int p);

t_list					*read_blocks(const int fd, int *size);

t_block					*create_block(char id, uint64_t bits);
int						validate_block(uint64_t bits);
void					delete_block(void *block);

#endif
