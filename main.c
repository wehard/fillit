/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/07 13:31:52 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int			throw_error(char *estr)
{
	ft_putendl_fd(estr, 2);
	return (1);
}

static int			ft_sqrt_next(int nb)
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

/*static void	free_blocks(t_list **alst)
{
	t_list	*tmp;

	if (alst && *alst)
	{
		while (*alst)
		{
			*alst = (*alst)->next;
			free(tmp);
			tmp = NULL;
		}
	}
}*/

int					main(int ac, char **av)
{
	int			fd;
	int			params[2];
	t_list		*b_lst;

	if (ac != 2)
		return (throw_error("usage: ./fillit file"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (throw_error("error opening file"));
	if (!(b_lst = read_blocks(fd, &params[1])))
	{
		close(fd);
		return (throw_error("block error"));
	}
	close(fd);
	params[0] = ft_sqrt_next(params[1] * 4);
	while (!(solve(b_lst, g_map_configs[params[0] - 2], params, 0)) &&
			params[0] - 2 < 9)
		params[0]++;
	print_b_lst(b_lst, params[1], params[0], FALSE);
	//free_blocks(&b_lst);
	return (0);
}
