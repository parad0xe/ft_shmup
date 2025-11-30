/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:39:13 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 16:41:00 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include <ncurses.h>
# include "ft_shmup.h"

// game_renderer
void		game_render(t_game *game, WINDOW *gamewin);

// ui_renderer
void		gameover_render(t_game *game, WINDOW *gameoverwin);
void		menu_render(t_game *game, WINDOW *menuwin);
void		pause_render(WINDOW *pausewin);

#endif
