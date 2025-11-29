/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 14:44:21 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <ncurses.h>

void	game_update_framerate(t_framerate *framerate)
{
	framerate->time_current = time_in_milliseconds();
	framerate->time_elapsed = framerate->time_current - framerate->time_prev;
	framerate->time_prev = framerate->time_current;
	framerate->accumulator += framerate->time_elapsed;
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
	werase(game->game_win);	
	wborder(game->menu_win, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(game->game_win, 0, 0, 0, 0, 0, 0, 0, 0);

	if (game->framerate.time_current - game->framerate.time_prev_fps >= 1000)
	{
		game->framerate.fps_display = game->framerate.fps_counter;
		game->framerate.fps_counter = 0;
		game->framerate.time_prev_fps = game->framerate.time_current;
	}

	mvwprintw(
		game->game_win,
		0, 0,
		"fps: %d",
		game->framerate.fps_display
	);
	mvwprintw(
		game->game_win,
		game->player.position[ROW],
		game->player.position[COL],
		"%c",
		game->player.sprite
	);
	print_game_entities(*game);
	
	mvwprintw(game->menu_win, 0, 0, "fps: %d", game->framerate.fps_display);
	
	wrefresh(game->menu_win);
	wrefresh(game->game_win);
}
