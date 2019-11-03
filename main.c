/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/03 18:14:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "fillit.h"
#include "libft.h"
#include <stdio.h>

static	t_block		*new_block(char id, uint16_t bits)
{
	t_block		*new;
	
	if (!(new = ft_memalloc(sizeof(t_block))))
		return (NULL);
	new->id = id;
	new->bits = bits;
	new->x = 0;
	new->y = 0;
	return (new);
}

static	uint16_t	shift_bits(uint16_t bits)
{
	while (!(bits & 61440)) /* 1111 0000 0000 0000 || 0xF000 */
		bits = bits << 4;
	while (!(bits & 34952)) /* 1000 1000 1000 1000 || 0x8888 */
		bits = bits << 1;
	return (bits);
}

static	uint16_t	get_bits(char *binary)
{
	uint16_t total;

	total = 0;
	while (*binary)
	{
		if (*binary == '\n')
		{
			binary++;
			continue;
		}
		total *= 2;
		if (*binary++ == '#')
			total += 1;
	}
	write(1, "shifted bits:\n", 14);
	total = shift_bits(total);
	ft_print_bits(total, 16);
	write(1, "\n", 1);
	return (total);
}

t_list				*read_blocks(const int fd)
{
	char		buf[BUF_SIZE + 1];
	int			i;
	int			n_read;
	uint16_t	bits;
	t_list		*blocks;
	t_list		*current;
	t_block		*test;

	blocks = ft_lstnew(0, 0);
	current = blocks;
	i = 0;
	while (i < 26 && (n_read = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[n_read] = '\0';
		printf("buffer:\n%s\n", buf);
		bits = get_bits(buf);
		current->content = new_block('A' + i, bits); /* validate needed here */
		test = current->content;
		printf("bits as decimal: %d index: %c\n\n", test->bits, test->id);
		current->content_size = sizeof(current->content);
		current->next = ft_lstnew(0, 0);
		current = current->next;
		i++;
	}
	return (blocks);
}

int					main(int ac, char **av)
{
	int		fd;
	t_list	*blocks;
	
	if (ac != 2)
	{
		ft_putendl("usage: ./fillit input_file");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (2);

	blocks = read_blocks(fd);
	/* solve(blocks); */
	close(fd);

	return (0);
}
