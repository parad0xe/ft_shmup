/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:56:54 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 03:08:21 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	set_enemy_badguy1(t_entity *enemy)
{
	enemy->type = ENEMY;
	enemy->sprite = '@';
	enemy->position = (t_xy){ 
		.x = GAME_WIDTH-1, 
		.y = randint(1, GAME_HEIGHT - 1) 
	};
	enemy->direction = (t_xy){ 
		.x = -1, 
		.y = 0 
	};
	enemy->speed = DEFAULT_ENEMY_SPEED/ MAX_FPS;
	enemy->active = 1;
	entity_set_weapon(enemy, '-', DEFAULT_BULLET_SPEED / MAX_FPS);
}
