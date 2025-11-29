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

#include <ncurses.h>
#include <unistd.h>

void	init_enemy(t_game_entity enemy, size_t	index)
{
	enemy.symbol = '@';
	enemy.type = ENEMY;
	enemy.sprite = NULL;
	enemy.position[ROW] = index;
	enemy.position[COL] = index % 25;
	enemy.direction = LEFT;
	enemy.active = FALSE;
}

void	init_entity_array(t_board board)
{
	size_t i;

	i = 0;
	while (i < ENTITY_ARRAY_SIZE)
	{
		init_enemy(board.board_array[i], i);
		++i;
	}
	
}

void	print_game_entities(t_game game)
{
	t_game_entity current;

	for (int i = 0; i < ENTITY_ARRAY_SIZE; ++i)
	{
		current = game.board.board_array[i];
		if(current.active)
			mvwprintw(game.game_win, current.position[ROW], current.position[COL], "%c", 'a');
		wrefresh(game.game_win);
	}
}

int	main(void)
{
	int row = 0;
	int col = 0;
	int	ch;

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	WINDOW	*menuwin = subwin(stdscr, 10, 0, row, col);
	WINDOW	*gamewin = subwin(stdscr, 70, 0, 10, 0);

	wborder(gamewin, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(menuwin, 0, 0, 0, 0, 0, 0, 0, 0);

	t_game game = {
		.is_over = 0,
		.player = {0},
		.menu_win = menuwin,
		.game_win = gamewin,
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

	// refresh();
	// wrefresh(win);
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
