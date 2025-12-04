/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:52:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/12/04 12:24:04 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include "entity.h"

void	set_player1(t_entity *player)
{
	player->type = PLAYER;
	player->sprite = '>';
	player->position = (t_xy){ 
		.x = GAME_WIDTH / 4,
		.y = GAME_HEIGHT / 2
	};
	player->direction = (t_xy){0};
	player->speed = 0;
	player->active = 1;
	entity_set_weapon(player, 'o', 160 / MAX_FPS);
}
