/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/05 13:19:41 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

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

static void			set_term_color(char c)
{
	ft_putstr("\033[1;");
	ft_putnbr((int)c - 'A' + 41);
	ft_putstr("m");
}

void				print_block_list(t_list *block_list, int size, int pretty)
{
	int				i;
	long			bit;
	char			*map;
	t_block			*cur_blk;

	map = ft_strnew(64);
	ft_memset(map, '.', 64);

	while (block_list->next)
	{
		cur_blk = block_list->content;
		i = 63;
		while (i)
		{
			bit = (cur_blk->pos >> i & 1);
			if (bit)
				map[63 - i] = cur_blk->id;
			i--;
		}
		block_list = block_list->next;
	}
	i = 0;
	while (map[i] && i < size * size)
	{
		if(pretty && map[i] != '.')
			set_term_color(map[i]);
		write(1, &(map[i]), 1);
		if (pretty)
			ft_putstr(" \033[0m");
		i++;
		if (i % size == 0)
			write(1, "\n", 1);
	}
	free(map);
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
			//printf("row switch\n");
			bits = bits >> (8 - size + w);
			y++;
			shift = 0;
			continue ;
		}
		else
			bits = bits >> 1;
		shift++;
	}
	//printf("y = %d, size = %d, shift = %d, w = %d, h = %d\n", y, size, shift, w, h);
	if (bits & map && (y == size - h))
		return (0);
	//printf("Adding block\n");
	return (bits);
}

void				solve(t_list *block_list, int n_blocks)
{
	uint64_t		map;
	t_list			*cur_lst;
	t_block			*cur_blk;

	cur_lst = block_list;
	map = 0;
	while (cur_lst->next)
	{
		cur_blk = cur_lst->content;
		n_blocks++; // !!
		//printf("Map %dx%d\n", n_blocks + 1, n_blocks + 1);
		//printf("Block.w = %d, Block.h = %d\n", cur_blk->x, cur_blk->y);
		if ((cur_blk->pos = check_spot(map, cur_blk->bits, 6, cur_blk->x, cur_blk->y)))
			map = map | cur_blk->pos;
		else
			cur_blk->pos = 0;
		cur_lst = cur_lst->next;
	}
	print_map(map);
}
