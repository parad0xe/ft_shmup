/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:56:54 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/04 12:27:33 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include "entity.h"

void	set_enemy_badguy1(t_entity *enemy)
{
	int	speed = randint(-10, 10) + DEFAULT_ENEMY_SPEED;

	enemy->type = ENEMY;
	enemy->sprite = '{';
	enemy->position = (t_xy){ 
		.x = GAME_WIDTH-1, 
		.y = randint(1, GAME_HEIGHT - 1) 
	};
	enemy->direction = (t_xy){
		.x = -1, 
		.y = 0 
	};
	enemy->speed = speed / MAX_FPS;
	enemy->active = 1;
	entity_set_weapon(enemy, '-', (speed - randint(50, 100)) / MAX_FPS);
}
