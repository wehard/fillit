/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:44:32 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/05 20:16:29 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <stdint.h>

typedef struct			s_vblock_data
{
	int					w;
	int					h;
	uint64_t			bits;
}						t_vblock_data;

typedef struct			s_block
{
	char				id;
	int					last;
	uint64_t			bits;
	uint64_t			pos;
}						t_block;

extern t_vblock_data 	g_valid_blocks[19];
extern uint64_t 		g_map_configs[7];

t_block					*create_block(char id, uint64_t bits, int last);
int						validate_block(uint64_t bits);
void					delete_block(void *block, size_t block_size);

#endif
