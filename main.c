/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/05 13:21:26 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

static int			throw_error(char *estr)
{
	ft_putstr_fd(estr, 2);
	return (1);
}

int					main(int ac, char **av)
{
	int			fd;
	int			n_blocks;
	t_list		*block_list;

	if (ac != 2)
		return (throw_error("usage: ./fillit input_file"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		return (throw_error("error opening file"));
	}
	if (!(block_list = read_blocks(fd, &n_blocks)))
	{
		close(fd);
		return (throw_error("block error"));
	}
	else
	{
		close(fd);
		solve(block_list, n_blocks);
		print_block_list(block_list, 8, TRUE);
		ft_lstdel(&block_list, &delete_block);
	}
	return (0);
}
