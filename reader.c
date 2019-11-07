/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:25:41 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 12:36:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

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
	uint64_t	total;
	int			i;

	total = 0;
	i = 0;
	while (*binary)
	{
		if (*binary == '\n')
		{
			i = 0;
			binary++;
			while (i < 4)
			{
				i++;
				total *= 2;
			}
			continue;
		}
		total *= 2;
		if (*binary++ == '#')
			total += 1;
	}
	if (!validate_block(total))
		return (0);
	else
		return (shift_bits_64(total));
}

t_list				*read_blocks(const int fd, int *n_blocks)
{
	char		buf[BUF_SIZE + 1];
	int			i;
	int			n_read;
	uint64_t	bits;
	t_list		*blocks;
	t_list		*current;

	*n_blocks = 0;
	blocks = ft_lstnew(0, 0);
	current = blocks;
	i = 0;
	while ((n_read = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[n_read] = '\0';
		bits = get_bits(buf);
		if (buf[n_read - 1] != '\n' || !bits)
			return (NULL);
		current->content = create_block('A' + i, bits, 0);
		current->content_size = sizeof(current->content);
		current->next = ft_lstnew(0, 0);
		current = current->next;
		i++;
		*n_blocks += 1;
	}
	current->next = blocks;
	return (blocks);
}
