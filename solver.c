/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 16:09:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				print_map(uint64_t map)
{
	int				i;
	long			bit;

	i = 64;
	write(1, "RESULT MAP:\n", 12);
	while (i--)
	{
		bit = (map >> i & 1) + '0';
		write(1, &bit, 1);
		if (i % 8 == 0)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

static uint64_t		fit_block(uint64_t map, uint64_t bits, int size, int w, int h)
{
	int	x;
	int y;

	x = w;
	y = h;
	while (bits & map && y < size)
	{
		x = w;
		while (bits & map && x < size)
		{
			bits = bits >> 1;
			x++;
		}
		y++;
	}
	return (map | bits);
}

void				solve(t_list *blocks, int n_blocks)
{
	uint64_t		map;
	uint64_t		bits;
	t_list			*cur_lst;
	t_block			*cur_blk;

	printf("Min map size: %d\n", n_blocks * 4);
	cur_lst = blocks;
	map = 0;
	while (cur_lst->next)
	{
		cur_blk = cur_lst->content;
		bits = cur_blk->bits;
		if (map)
			map = fit_block(map, bits, n_blocks * 4);
		else
			map = bits;
		print_map(map);
		cur_lst = cur_lst->next;
	}
	
}
