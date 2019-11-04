/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 15:02:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		print_map(uint64_t map)
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

void		solve(t_list *blocks, int n_blocks)
{
	uint64_t		map;
	uint64_t		bits;
	t_block			*current;

	current = blocks->content;
	bits = current->bits;
	map = bits;
	print_map(map);
	printf("Min map size: %d\n", n_blocks * 4);
}
