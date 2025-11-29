/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 13:15:06 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

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
	box(game->win, 0, 0);
	
	if (game->framerate.time_current - game->framerate.time_prev_fps >= 1000)
	{
		game->framerate.fps_display = game->framerate.fps_counter;
		game->framerate.fps_counter = 0;
		game->framerate.time_prev_fps = game->framerate.time_current;
	}

	mvwprintw(
		game->win,
		0, 0,
		"fps: %d",
		game->framerate.fps_display
	);
	mvwprintw(
		game->win,
		game->player.position[Y],
		game->player.position[X],
		"%c",
		game->player.sprite
	);
}
