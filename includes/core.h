/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:29:52 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 16:40:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "ft_shmup.h"

void		game_init(t_game *game);
int			game_shoot(t_game *game, t_entity shooter, void (*set_bullet)(t_entity shooter, t_entity *bullet));
int			game_add_enemy(t_game *game);
void		game_update(t_game *game);

#endif
