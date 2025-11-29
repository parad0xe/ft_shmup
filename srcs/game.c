/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 10:47:38 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <ncurses.h>

void	game_update_framerate(t_game *game)
{
	game->framerate.time_current = timeInMilliseconds();
	game->framerate.time_elapsed = game->framerate.time_current - game->framerate.time_prev;
	game->framerate.time_prev = game->framerate.time_current;
	game->framerate.accumulator += game->framerate.time_elapsed;
}

void	game_update(t_game *game)
{
	while (game->framerate.accumulator >= game->framerate.delta)
	{
		// update
		game->framerate.accumulator -= game->framerate.delta;
		game->framerate.fps_counter++;
	}
}

void	game_render(t_game *game)
{
	if (game->framerate.time_current - game->framerate.time_prev_fps >= 1000)
	{
		game->framerate.fps_display = game->framerate.fps_counter;
		game->framerate.fps_counter = 0;
		game->framerate.time_prev_fps = game->framerate.time_current;
	}

	print_game_entities(*game);
	wrefresh(game->menu_win);
	mvwprintw(game->menu_win, 0, 0, "fps: %d", game->framerate.fps_display);
	wrefresh(game->menu_win);
}
