/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:44:32 by nlallema          #+#    #+#             */
/*   Updated: 2025/12/04 12:17:31 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	set_background(t_entity *slot)
{
	double	random = randfloat(0, 1);
	slot->type = BACKGROUND;
	if (random < 0.3)
	{
		slot->sprite = 'o';
		slot->speed = 200 / MAX_FPS;
	}
	else if (random < 0.7)
	{
		slot->sprite = '*';
		slot->speed = 300 / MAX_FPS;
	}
	else	
	{
		slot->sprite = '.';
		slot->speed = 100 / MAX_FPS;
	}
	slot->position = (t_xy){ 
		.x = GAME_WIDTH-2, 
		.y = randint(1, GAME_HEIGHT - 1) 
	};
	slot->direction = (t_xy){ 
		.x = -1, 
		.y = 0 
	};
	slot->weapon = (t_weapon){0};
	slot->active = 1;
}

void	set_background_randpos(t_entity *slot)
{
	double	random = randfloat(0, 1);
	slot->type = BACKGROUND;
	if (random < 0.3)
	{
		slot->sprite = 'o';
		slot->speed = 300 / MAX_FPS;
	}
	else if (random < 0.7)
	{
		slot->sprite = '*';
		slot->speed = 400 / MAX_FPS;
	}
	else	
	{
		slot->sprite = '.';
		slot->speed = 500 / MAX_FPS;
	}
	slot->position = (t_xy){
		.x = randint(1, GAME_WIDTH - 1),
		.y = randint(1, GAME_HEIGHT - 1)
	};
	slot->direction = (t_xy){ 
		.x = -1, 
		.y = 0 
	};
	slot->weapon = (t_weapon){0};
	slot->active = 1;
}
