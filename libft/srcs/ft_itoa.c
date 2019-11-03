/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:09:29 by srouhe            #+#    #+#             */
/*   Updated: 2019/10/18 18:09:23 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*ft_populate_string(char *r, int i, unsigned int nb)
{
	while (nb >= 10)
	{
		r[i--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	r[i] = (char)(nb % 10 + 48);
	return (r);
}

char			*ft_itoa(int n)
{
	int				i;
	unsigned int	flag;
	unsigned int	nb;
	unsigned int	len;
	char			*r;

	flag = 0;
	if (n < 0)
	{
		nb = (unsigned int)n * -1;
		flag = 1;
	}
	else
		nb = (unsigned int)n;
	len = ft_count_digits(nb);
	if (!(r = (char *)malloc(sizeof(char) * (len + 1 + flag))))
		return (NULL);
	i = len - 1 + flag;
	if (flag)
		r[0] = '-';
	r = ft_populate_string(r, i, nb);
	r[len + flag] = '\0';
	return (r);
}
