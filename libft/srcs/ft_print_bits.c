/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:54:45 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/03 16:00:44 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_bits(long octet, int len)
{
	int				i;
	long			bit;

	i = len;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
		if (i % 4 == 0)
			write(1, "\n", 1);
	}
}
