/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:52:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 03:08:34 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void    set_player1(t_entity *player)
{
    player->type = PLAYER;
    player->sprite = '>';
    player->position = (t_xy){ 
        .x = 1, 
        .y = GAME_HEIGHT / 2 
    };
    player->direction = (t_xy){0};
    player->speed = 0;
    player->active = 1;
    entity_set_weapon(player, '-', 160 / MAX_FPS);
}
