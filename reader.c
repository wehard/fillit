/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:25:41 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/05 20:11:02 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

static	uint64_t	shift_bits_64(uint64_t bits)
{
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
	//write(1, "shifted bits:\n", 14);
	total = shift_bits_64(total);
	return (total);
}

t_list				*read_blocks(const int fd, int *n_blocks)
{
	char		buf[BUF_SIZE + 1];
	int			i;
	int			n_read;
	int			g_index;
	uint64_t	bits;
	t_list		*blocks;
	t_list		*current;

	blocks = ft_lstnew(0, 0);
	current = blocks;
	i = 0;
	while (i < 26 && (n_read = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[n_read] = '\0';
		//printf("buffer:\n%s\n", buf);
		bits = get_bits(buf);
		if (buf[n_read - 1] != '\n')
			return (NULL);
		if ((g_index = validate_block(bits)) < 0)
			return (NULL);
		current->content = create_block('A' + i, bits, 0);
		//printf("bits as decimal: %llu index: %c\n\n", test->bits, test->id);
		current->content_size = sizeof(current->content);
		current->next = ft_lstnew(0, 0);
		current = current->next;
		i++;
		*n_blocks += 1;
	}
	current->next = blocks;
	return (blocks);
}
