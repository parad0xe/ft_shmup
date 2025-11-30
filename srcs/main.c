/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 17:06:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include "core.h"
#include "renderer.h"

static void	_configure_global_components(void)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	notimeout(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	srand(time(NULL));
	if (has_colors() == FALSE)
	{
		endwin();
		write(2, ERR_NOCOLORS, strlen(ERR_NOCOLORS));
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
}

static void	_run_game(t_game *game, t_windows windows)
{
	int	x, y;
	int origin_x, origin_y;

	getmaxyx(stdscr, origin_y, origin_x);
	game_init(game);
	while (game->status != OVER && game->status != STOPPED)
	{
		handle_input(game);
		getmaxyx(stdscr, y, x);
		if (x != origin_x || y != origin_y)
		{
			game->status = STOPPED;
			endwin();
			write(2, ERR_RESIZED, strlen(ERR_RESIZED));
		}
		if (game->status != PAUSED)
			game_update(game);
		menu_render(game, windows.menuwin);
		if (game->status != PAUSED)
			game_render(game, windows.gamewin);
		else
			pause_render(windows.pausewin);
		wresize(windows.menuwin, y, x);
	}
	if (game->status == OVER)
		gameover_render(game, windows.gameoverwin);
}

int	main(void)
{
	int		x, y;
	int		center_x, center_y;
	t_game	game;

	_configure_global_components();
	if (!stdscr)
	{
		write(2, MEMORY_ERROR_MSG, strlen(MEMORY_ERROR_MSG));
		return (1);
	}
	getmaxyx(stdscr, y, x);
	center_x = x / 2;
	center_y = y / 2;
	WINDOW	*menuwin = subwin(stdscr, MENU_HEIGHT, MENU_WIDTH, center_y - MENU_HEIGHT - GAME_HEIGHT / 2, center_x - MENU_WIDTH / 2);
	WINDOW	*gamewin = subwin(stdscr, GAME_HEIGHT, GAME_WIDTH, center_y - GAME_HEIGHT / 2, center_x - GAME_WIDTH / 2);
	WINDOW	*pausewin = subwin(stdscr, PAUSE_HEIGHT, PAUSE_WIDTH, center_y - PAUSE_HEIGHT / 2, center_x - PAUSE_WIDTH / 2);
	WINDOW	*gameoverwin = subwin(stdscr, GAMEOVER_HEIGHT, GAMEOVER_WIDTH, center_y - GAMEOVER_HEIGHT / 2, center_x - GAMEOVER_WIDTH / 2);

	t_windows windows = {
		.gamewin = gamewin,
		.menuwin = menuwin,
		.pausewin = pausewin,
		.gameoverwin = gameoverwin
	};
	if (!menuwin || !gamewin || !pausewin || !gameoverwin)
	{
		endwin();
		write(2, MEMORY_ERROR_MSG, strlen(MEMORY_ERROR_MSG));
		return (1);
	}
	while (game.status != STOPPED)
	{
		_run_game(&game, windows);
		while (game.status != STOPPED && game.status != RUNNING)
		{
			handle_input(&game);
			usleep(50);
		}
	}
	endwin();
	return (0);
}
