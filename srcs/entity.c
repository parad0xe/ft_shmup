/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:37:51 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/29 20:23:47 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

int		check_collisions(t_game_entity entity, t_game_entity *others)
{
	(void)entity;
	(void)others;
	return (0) ;//TODO: implement
}

void	shoot(t_board *board, t_game_entity *entity)
{
	(void)board;
	(void)entity;
	//TODO: make entities shoot (with correct directions according to their type)
}

/**
 * @brief for each row, choose at random wether to spawn an enemy.
 */
void	generate_wave(void)
{
	//TODO: write a function that randomly creates enemies or not for each row.
	for (int i = 0; i < GAME_HEIGHT; ++i)
	
		if (rand() / RAND_MAX > 0.7 )
		{
			
		}
}

int	add_entity(t_board *board, t_type type)
{
	(void)board;
	(void)type;
	// determines the first free index, and adds a random entity .
	return (0);
}

/**
 * @brief creates an ennemy on given position on given row
 */
void	generate_enemy(t_board *board, int row)
{
	(void)board;
	(void)row;
	//TODO: implement this function
}
/**
	* @brief makes passed entity advance according to its direction.
*/
int	advance_entity(t_game_entity *entity)
{
	entity->position[ROW] += entity->direction[ROW];
	entity->position[COL] += entity->direction[COL];
	return (0);
}
