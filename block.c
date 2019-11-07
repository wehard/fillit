/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:27:50 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 13:29:29 by srouhe           ###   ########.fr       */
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

uint64_t	g_valid_blocks[19] =
{
	9259542121117908992ULL,
	17293822569102704640ULL,
	13889101250810609664ULL,
	9259611940106272768ULL,
	16176929861514821632ULL,
	13853142822535823360ULL,
	2368893403996880896ULL,
	13871227589789483008ULL,
	9286422431637962752ULL,
	4629911523169402880ULL,
	16149908263750598656ULL,
	13862079653046386688ULL,
	4665869951444189184ULL,
	6971572223169527808ULL,
	9277485601127399424ULL,
	9277555969871577088ULL,
	16158915463005339648ULL,
	4665799582700011520ULL,
	4674736413210574848ULL
};

t_block			*create_block(char id, uint64_t bits)
{
	t_block		*new_block;

	if (!(new_block = ft_memalloc(sizeof(t_block))))
		return (NULL);
	new_block->id = id;
	new_block->bits = bits;
	new_block->pos = 0;
	return (new_block);
}

int				validate_block(uint64_t bits)
{
	int i;

	i = 1;
	while (i <= 19)
	{
		if (bits == g_valid_blocks[i - 1])
			return (i);
		i++;
	}
	return (0);
}

void			delete_block(void *block)
{
	free(block);
}
