/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 11:29:58 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

#include <unistd.h>

int	main(void)
{
	int width = 300;
	int height = 300;
	int row = 0;
	int col = 0;
	int	ch;

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	WINDOW *win = newwin(height, width, row, col);
	mvwprintw(win, 7, 0, "You pressed the up arrow key");

	t_game game = {
		.is_over = 0,
		.player = {0},
		.framerate = {
			.time_prev = timeInMilliseconds(),
			.time_current = 0,
			.time_elapsed = 0,
			.time_prev_fps = 0,
			.delta = 1000.0 / 60.,
			.accumulator = 0.0,
			.fps_counter = 0,
			.fps_display = 0
		}
	};


	while (!game.is_over)
	{
		game_update_framerate(&game);

		// handlers
		ch = getch();
		if (ch == 'q')
			break ;
	
		game_update(&game);
		game_render(&game);
		refresh();
	}

	endwin();
	return (0);
}
