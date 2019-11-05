/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:27:50 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/05 19:04:53 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "block.h"

uint64_t		g_map_configs[7] =
{
	4557642822898941951ULL,
	2242546323825885183ULL,
	1085102596613472255ULL,
	506381209882853375ULL,
	217020518514294783ULL,
	72340172838076927ULL,
	0
};

t_vblock_data	g_valid_blocks[19] =
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

t_block			*create_block(char id, uint64_t bits, int w, int h)
{
	t_block		*new_block;

	if (!(new_block = ft_memalloc(sizeof(t_block))))
		return (NULL);
	new_block->id = id;
	new_block->bits = bits;
	new_block->x = w;
	new_block->y = h;
	new_block->pos = 0;
	return (new_block);
}

int				validate_block(uint64_t bits)
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

void			delete_block(void *block, size_t block_size)
{
	free(block);
	block_size++;
}
