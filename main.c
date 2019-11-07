/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/07 16:54:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int			throw_error(char *estr, int error)
{
	ft_putendl_fd(estr, 1);
	return (error);
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

int					main(int ac, char **av)
{
	int			fd;
	int			params[2];
	t_list		*b_lst;

	params[0] = 0;
	params[1] = 0;
	if (ac != 2)
		return (throw_error("usage: ./fillit file", 1));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (throw_error("error", 2));
	if (!(b_lst = read_blocks(fd, &params[1])))
	{
		close(fd);
		return (throw_error("error", 3));
	}
	close(fd);
	params[0] = ft_sqrt_next(params[1] * 4);
	while (!(solve(b_lst, g_map_configs[params[0] - 2], params, 0)) &&
			params[0] - 2 < 9)
		params[0]++;
	print_b_lst(b_lst, params[1], params[0]);
	return (0);
}
