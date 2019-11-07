/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/07 13:50:46 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void			set_term_color(char c)
{
	ft_putstr("\033[1;");
	ft_putnbr((int)c - 'A' + 41);
	ft_putstr("m");
}

static void			print_map(char *map, int size, int p)
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
		if (p && map[ijr[0]] != '.')
			set_term_color(map[ijr[0]]);
		write(1, &(map[ijr[0]]), 1);
		if (p)
			ft_putstr(" \033[0m");
		ijr[0]++;
		ijr[1]++;
	}
}

void				print_b_lst(t_list *b_lst, int nb, int size, int p)
{
	int				i;
	long			bit;
	char			*map;
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
		b_lst = b_lst->next;
	}
	print_map(map, size, p);
	free(map);
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
