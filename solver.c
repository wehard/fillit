/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/05 20:41:36 by srouhe           ###   ########.fr       */
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

void				print_block_list(t_list *block_list, int n_blocks , int size, int pretty)
{
	int				i;
	long			bit;
	char			*map;
	t_block			*cur_blk;

	map = ft_strnew(64);
	ft_memset(map, '.', 64);

	while (block_list->next && n_blocks--)
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

static uint64_t		check_spot(int shift, uint64_t map, uint64_t bits)
{	
	bits = bits >> shift;
	if (map & bits)
	{
		//printf("No fit\n");
		return (0);
	}
	//printf("Placing bit\n");
	return (bits);
}

int				solve(t_list *block_list, uint64_t map, int size, int i, int num_blocks)
{
	int				shift;
	t_list			*cur_lst;
	t_block			*cur_blk;

	if (i == num_blocks)
		return (1);
	shift = 0;
	cur_lst = block_list;
	while (shift < size * size)
	{
		cur_blk = cur_lst->content;		
		if ((cur_blk->pos = check_spot(shift, map, cur_blk->bits)))
		{
			map |= cur_blk->pos;
			if (solve(cur_lst->next, map, size, i + 1, num_blocks))
				return (1);
			else
			{
				map &= ~cur_blk->pos; 
				cur_blk->pos = 0;
			}
		}
		shift++;
	}
	return (0);
}
