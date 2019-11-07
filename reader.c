/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:25:41 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 16:20:01 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static	uint64_t	shift_bits_64(uint64_t bits)
{
	if (!bits)
		return (bits);
	while (!(bits & 0xFF00000000000000))
		bits = bits << 8;
	while (!(bits & 0x8080808000000000))
		bits = bits << 1;
	return (bits);
}

static uint64_t		get_bits(char *binary)
{
	uint64_t	bits;
	int			i;

	bits = 0;
	i = 0;
	while (*binary)
	{
		if (*binary == '\n')
		{
			i = 0;
			binary++;
			while (i++ < 4)
				bits *= 2;
			continue;
		}
		bits *= 2;
		if (*binary++ == '#')
			bits += 1;
	}
	return (shift_bits_64(bits));
}

t_list				*read_blocks(const int fd, int *nb)
{
	char		buf[BUF_SIZE + 1];
	int			n_read;
	uint64_t	bits;
	t_list		*blocks;
	t_list		*current;

	blocks = ft_lstnew(0, 0);
	current = blocks;
	while ((n_read = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[n_read] = '\0';
		bits = get_bits(buf);
		if (buf[n_read - 1] != '\n' || (buf[0] != '.' && buf[0] != '#')
			|| !(validate_block(bits)))
			return (NULL);
		current->content = create_block('A' + *nb, bits);
		current->content_size = sizeof(current->content);
		current->next = ft_lstnew(0, 0);
		current = current->next;
		*nb += 1;
	}
	if (!blocks || ft_strlen(buf) != 20)
		return (NULL);
	current->next = blocks;
	return (blocks);
}
