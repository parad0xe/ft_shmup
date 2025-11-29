/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 10:49:42 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"


int	main(void)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	t_game game = {
		.is_over = 0,
		.player = {0};
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

	int			ch;

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

	getch();
	endwin();
	return (0);
}
