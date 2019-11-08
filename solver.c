/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/07 16:49:30 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void			print_map(char *map, int size)
{
	int ijr[3];

	ijr[0] = 0;
	ijr[1] = 0;
	ijr[2] = 0;
	while (map[ijr[0]])
	{
		if (ijr[2] == size)
			break ;
		if (ijr[1] == size)
		{
			write(1, "\n", 1);
			ijr[0] += 8 - size;
			ijr[1] = 0;
			ijr[2]++;
			continue ;
		}
		write(1, &(map[ijr[0]]), 1);
		ijr[0]++;
		ijr[1]++;
	}
	free(map);
}

void				print_b_lst(t_list *b_lst, int nb, int size)
{
	int				i;
	long			bit;
	char			*map;
	t_list			*tmp;
	t_block			*cur_blk;

	map = ft_strnew(64);
	ft_memset(map, '.', 64);
	while (b_lst->next && nb--)
	{
		cur_blk = b_lst->content;
		i = 63;
		while (i)
		{
			bit = (cur_blk->pos >> i & 1);
			if (bit)
				map[63 - i] = cur_blk->id;
			i--;
		}
		tmp = b_lst;
		b_lst = b_lst->next;
		free_block(&tmp);
	}
	free_block(&b_lst);
	print_map(map, size);
}

static uint64_t		check_spot(int shift, uint64_t map, uint64_t bits)
{
	bits = bits >> shift;
	if (map & bits)
		return (0);
	return (bits);
}

int					solve(t_list *b_lst, uint64_t map, int *params, int i)
{
	int				shift;
	int				shiftmax;
	t_block			*cur_blk;

	if (i == params[1])
		return (1);
	shift = 0;
	shiftmax = (params[0] + 1) * (params[0] + 1);
	while (shift < shiftmax)
	{
		cur_blk = b_lst->content;
		if ((cur_blk->pos = check_spot(shift, map, cur_blk->bits)))
		{
			map |= cur_blk->pos;
			if (solve(b_lst->next, map, params, i + 1))
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
