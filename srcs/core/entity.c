/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:37:51 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 02:14:57 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include "core.h"

int	entity_check_collision(t_entity entity, t_entity other)
{
	if (entity.active && other.active)
		if (entity.position.x == other.position.x)
			if (entity.position.y == other.position.y)
				return (1);
	return (0);
}

void	entity_set_weapon(t_entity *entity, char sprite, int speed)
{
	entity->weapon.sprite = sprite;
	entity->weapon.speed = speed;
	entity->weapon.active = 1;
	entity->weapon.shooting_rate = DEFAULT_SHOOTING_RATE / MAX_FPS;
}

/**
	* @brief makes passed entity advance according to its direction.
*/
int	entity_advance(t_entity *entity)
{
	entity->position.y += entity->direction.y;
	entity->position.x += entity->direction.x;
	return (1);
}

/**
 * @brief for each row, choose at random wether to spawn an enemy.
 */
void	generate_wave(t_game *game)
{
	for (int i = 0; i < 8; ++i)
	{
		if (randint(0, 100) < 50)
			game_add_enemy(game);
	}
}
