/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 13:47:23 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

#include <unistd.h>

int	main(void)
{
	int	ch;

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	t_game game = {
		.win = newwin(HEIGHT, WIDTH, 0, 0),
		.is_over = 0,
		.player = {
			.sprite = '>',
			.type = PLAYER,
			.position = { 1, HEIGHT / 2  },
			.direction = {0, 0},
			.speed = 0
		},
		.framerate = {
			.time_prev = time_in_milliseconds(),
			.time_current = 0,
			.time_elapsed = 0,
			.time_prev_fps = 0,
			.delta = 1000.0 / 60.,
			.accumulator = 0.0,
			.fps_counter = 0,
			.fps_display = 0
		}
	};
	nodelay(game.win, TRUE);
	notimeout(game.win, TRUE);
	keypad(game.win, TRUE);
	
	while (!game.is_over)
	{
		game_update_framerate(&game.framerate);

		// handlers
		ch = wgetch(game.win);
		switch (ch)
		{
			case 113:
				game.is_over = 1;
				break ;
			case KEY_UP:
				game.player.position[Y] -= 1;
				break ;
			case KEY_DOWN:
				game.player.position[Y] += 1;
				break ;
		}
		game_update(&game);
		werase(game.win);
		game_render(&game);
		wrefresh(game.win);
	}

	endwin();
	return (0);
}
