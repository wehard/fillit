/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:32:53 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/04 19:23:07 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_vblock_data g_valid_blocks[19] =
{
	{1, 4, 9259542121117908992ULL},
	{4, 1, 17293822569102704640ULL},
	{2, 2, 13889101250810609664ULL},
	{2, 3, 9259611940106272768ULL},
	{3, 2, 16176929861514821632ULL},
	{2, 3, 13853142822535823360ULL},
	{3, 2, 2368893403996880896ULL}, 
	{2, 3, 13871227589789483008ULL},
	{3, 2, 9286422431637962752ULL}, 
	{2, 3, 4629911523169402880ULL}, 
	{3, 2, 16149908263750598656ULL},
	{3, 2, 13862079653046386688ULL},
	{2, 3, 4665869951444189184ULL}, 
	{3, 2, 6971572223169527808ULL}, 
	{2, 3, 9277485601127399424ULL}, 
	{2, 3, 9277555969871577088ULL}, 
	{3, 2, 16158915463005339648ULL},
	{2, 3, 4665799582700011520ULL}, 
	{3, 2, 4674736413210574848ULL} 
};

static	t_block		*new_block(char id, uint64_t bits, int w, int h)
{
	t_block		*new;
	
	if (!(new = ft_memalloc(sizeof(t_block))))
		return (NULL);
	new->id = id;
	new->bits = bits;
	new->x = w;
	new->y = h;
	new->pos = 0;
	return (new);
}

static	uint16_t	shift_bits_16(uint16_t bits)
{
	while (!(bits & 0xF000)) /* 1111 0000 0000 0000 || 0xF000 */
		bits = bits << 4;
	while (!(bits & 0x8888)) /* 1000 1000 1000 1000 || 0x8888 */
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

static	uint64_t	get_bits(char *binary)
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
	return (total);
}

static int	validate_block(uint64_t bits)
{
	int i;

	i = 0;
	while (i < 19)
	{
		if (bits == g_valid_blocks[i].bits)
			return (i);
		i++;
	}
	return (-1);
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
	t_block		*test;

	blocks = ft_lstnew(0, 0);
	current = blocks;
	i = 0;
	while (i < 26 && (n_read = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[n_read] = '\0';
		printf("buffer:\n%s\n", buf);
		bits = get_bits(buf);
		if (buf[n_read - 1] != '\n')
			return (NULL);
		if ((g_index = validate_block(bits)) < 0)
			return (NULL);
		current->content = new_block('A' + i, bits, g_valid_blocks[g_index].w, g_valid_blocks[g_index].h);

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

void 	del_block(void *block, size_t block_size)
{
	free(block);
	block_size++;
}

static int			throw_error(char *estr)
{
	ft_putstr_fd(estr, 2);
	return (1);
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
	if (!blocks)
		return (throw_error("Block error!"));
	close(fd);
	solve(blocks, n_blocks);
	ft_lstdel(&blocks, &del_block);
	while(1);
	return (0);
}
