/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:12:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/29 16:12:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	init_enemy(t_game_entity enemy, size_t	index)
{
	enemy.type = ENEMY;
	enemy.sprite = '@';
	enemy.position[ROW] = index;
	enemy.position[COL] = index % 25;
	enemy.direction[ROW] = UP;
	enemy.direction[COL] = LEFT;
	enemy.active = FALSE;
}

void	init_entity_array(t_board board)
{
	size_t i;

	i = 0;
	while (i < ENTITY_ARRAY_SIZE)
	{
		init_enemy(board.board_array[i], i);
		++i;
	}
}
