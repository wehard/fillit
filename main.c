/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 15:01:42 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static	t_block		*new_block(char id, uint64_t bits)
{
	t_block		*new;
	
	if (!(new = ft_memalloc(sizeof(t_block))))
		return (NULL);
	new->id = id;
	new->bits = bits;
	new->x = 0;
	new->y = 0;
	new->pos = 0;
	return (new);
}

static	uint16_t	shift_bits_16(uint16_t bits)
{
	while (!(bits & 61440)) /* 1111 0000 0000 0000 || 0xF000 */
		bits = bits << 4;
	while (!(bits & 34952)) /* 1000 1000 1000 1000 || 0x8888 */
		bits = bits << 1;
	return (bits);
}

static	uint64_t	shift_bits_64(uint64_t bits)
{
	while (!(bits & 0xFF00000000000000))
		bits = bits << 8;
	while (!(bits & 0x8080808000000000))
		bits = bits << 1;
	return (bits);
}

static	uint64_t	get_bits(char *binary) /* Validointi */
{
	uint64_t 	total;
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
	write(1, "shifted bits:\n", 14);
	total = shift_bits_64(total);
	print_map(total);
	write(1, "\n", 1);
	return (total);
}

t_list				*read_blocks(const int fd, int *n_blocks)
{
	char		buf[BUF_SIZE + 1];
	int			i;
	int			n_read;
	uint64_t	bits;
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
		current->content = new_block('A' + i, bits);
		test = current->content;
		printf("bits as decimal: %llu index: %c\n\n", test->bits, test->id);
		current->content_size = sizeof(current->content);
		current->next = ft_lstnew(0, 0);
		current = current->next;
		i++;
		*n_blocks += 1;
	}
	return (blocks);
}

int					main(int ac, char **av)
{
	int			fd;
	int			n_blocks;
	t_list		*blocks;
	
	if (ac != 2)
	{
		ft_putendl("usage: ./fillit input_file");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (2);

	blocks = read_blocks(fd, &n_blocks);
	close(fd);
	solve(blocks, n_blocks);
	return (0);
}
