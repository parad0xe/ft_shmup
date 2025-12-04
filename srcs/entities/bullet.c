/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:49:46 by nlallema          #+#    #+#             */
/*   Updated: 2025/12/04 12:17:04 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void    set_bullet1(t_entity shooter, t_entity *bullet)
{
    if (shooter.type == PLAYER)
    {
        bullet->type = PLAYER_LASER;
        bullet->direction.x = 1;
        bullet->direction.y = 0;
    }
    else
    {
        bullet->type = ENEMY_LASER;
        bullet->direction.x = shooter.direction.x;
        bullet->direction.y = shooter.direction.y;
    }
    bullet->sprite = shooter.weapon.sprite;
    bullet->weapon = (t_weapon){0};
    bullet->sprite = shooter.weapon.sprite;
    bullet->speed = shooter.weapon.speed;
    bullet->position.x = shooter.position.x + shooter.direction.x;
    bullet->position.y = shooter.position.y + shooter.direction.y;
    bullet->active = 1;
}

void		set_enemy_bullet1(t_entity shooter, t_entity *bullet)
{
	bullet->type = ENEMY_LASER;
	bullet->direction.x = shooter.direction.x;
	bullet->direction.y = shooter.direction.y;
    bullet->sprite = shooter.weapon.sprite;
    bullet->weapon = (t_weapon){0};
    bullet->sprite = shooter.weapon.sprite;
    bullet->speed = shooter.weapon.speed;
    bullet->position.x = shooter.position.x + shooter.direction.x;
    bullet->position.y = shooter.position.y + shooter.direction.y;
    bullet->active = 1;

}
