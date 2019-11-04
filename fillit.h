/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:35:38 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 14:58:14 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H

# define FILLIT_H

# define BUF_SIZE 21

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

enum
{
	VERTICAL = 34952,
	HORZONTAL = 15,
	SQUARE = 52224,
	L = 35008,
	L_ROT_90 = 59392,
	L_ROT_180 = 50240,
	L_ROT_270 = 11776,
	INV_L = 51328,
	INV_L_ROT_90 = 57856,
	INV_L_ROT_180 = 17600,
	INV_L_ROT_270 = 36352
};

typedef struct		s_block
{
	char			id;
	uint64_t		bits;
	uint64_t		pos;
	uint8_t			x;
	uint8_t			y;


}					t_block;

typedef struct		s_map
{
	int				size;
	uint64_t		map;

}					t_map;

void				solve(t_list *blocks, int n_blocks);
void				print_map(uint64_t map);

#endif
