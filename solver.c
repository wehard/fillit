/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 18:16:30 by srouhe           ###   ########.fr       */
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

static uint64_t		check_spot(uint64_t map, uint64_t bits, int size, int w, int h)
{
	int shift;
	int y;

	y = 0;
	shift = 0;
	while (bits & map && y < size - h)
	{
		if (shift + w == size)
		{
			printf("row switch\n");
			bits = bits >> (8 - size + w);
			y++;
			shift = 0;
			continue ;
		}
		else
			bits = bits >> 1;
		shift++;
	}
	printf("y = %d, size = %d, shift = %d, w = %d, h = %d\n", y, size, shift, w, h);
	if (bits & map && (y == size - h))
		return (0);
	printf("Adding block\n");
	return (bits);
}

void				solve(t_list *blocks, int n_blocks)
{
	uint64_t		map;
	t_list			*cur_lst;
	t_block			*cur_blk;

	cur_lst = blocks;
	map = 0;
	while (cur_lst->next)
	{
		cur_blk = cur_lst->content;
		printf("Map %dx%d\n", n_blocks + 1, n_blocks + 1);
		printf("Block.w = %d, Block.h = %d\n", cur_blk->x, cur_blk->y);
		if ((cur_blk->pos = check_spot(map, cur_blk->bits, 5, cur_blk->x, cur_blk->y)))
			map = map | cur_blk->pos;
		print_map(map);
		cur_lst = cur_lst->next;
	}
	
}
