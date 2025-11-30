/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:38:57 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 16:39:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "ft_shmup.h"

int			entity_advance(t_entity *entity);
int			entity_check_collision(t_entity entity, t_entity other);
void		entity_set_weapon(t_entity *entity, char sprite, int speed);
void		generate_wave(t_game *game);

#endif
