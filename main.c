/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/05 20:28:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

static int			throw_error(char *estr)
{
	ft_putstr_fd(estr, 2);
	return (1);
}

int		ft_sqrt(int nb)
{
	int	i;
	int sqrt;

	i = 1;
	if (!nb)
		return (0);
	while (i <= nb)
	{
		sqrt = i * i;
		if (sqrt == nb)
			return (i);
		else if (sqrt < nb)
			i++;
		else
		{
			i = 1;
			nb += 1;
		}
	}
	return (0);
}

int					main(int ac, char **av)
{
	int			fd;
	int			num_blocks;
	int			size;
	t_list		*block_list;

	if (ac != 2)
		return (throw_error("usage: ./fillit input_file"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		return (throw_error("error opening file"));
	}
	if (!(block_list = read_blocks(fd, &num_blocks)))
	{
		close(fd);
		return (throw_error("block error"));
	}
	close(fd);
	size = ft_sqrt(num_blocks * 4);
	printf("Blocks: %d sqrt: %d\n", num_blocks, size);
	while (!(solve(block_list, g_map_configs[size - 2], size, 0, num_blocks)) && size - 2 < 9)
	{	
		printf("Incrementing size from %d to %d\n", size, size + 1);
		size++;
	}
	print_block_list(block_list, num_blocks, 8, TRUE);
	//ft_lstdel(&block_list, &delete_block);
	return (0);
}
