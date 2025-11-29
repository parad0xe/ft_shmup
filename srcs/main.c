/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 14:43:13 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

#include <ncurses.h>
#include <unistd.h>

void	init_enemy(t_game_entity enemy, size_t	index)
{
	enemy.type = ENEMY;
	enemy.sprite = '@';
	enemy.position[ROW] = index;
	enemy.position[COL] = index % 25;
	enemy.direction[COL] = LEFT;
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
		//wrefresh(game.game_win);
	}
}

int	main(void)
{
	int	ch;

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	
	WINDOW	*menuwin = subwin(stdscr, MENU_HEIGHT, 0, 0, 0);
	WINDOW	*gamewin = subwin(stdscr, GAME_HEIGHT, 0, 10, 0);

	t_game game = {
		.is_over = 0,
		.player = {
			.sprite = '>',
			.type = PLAYER,
			.position = { 1, GAME_HEIGHT / 2  },
			.direction = {0, 0},
			.speed = 0
		},
		.menu_win = menuwin,
		.game_win = gamewin,
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
	nodelay(game.game_win, TRUE);
	notimeout(game.game_win, TRUE);
	keypad(game.game_win, TRUE);
	
	while (!game.is_over)
	{
		game_update_framerate(&game.framerate);

		// handlers
		ch = wgetch(game.game_win);
		switch (ch)
		{
			case 113:
				game.is_over = 1;
				break ;
			case KEY_UP:
				game.player.position[ROW] -= 1;
				break ;
			case KEY_DOWN:
				game.player.position[ROW] += 1;
				break ;
		}
		game_update(&game);
		game_render(&game);
	}

	endwin();
	return (0);
}
