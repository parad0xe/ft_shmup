/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 04:01:33 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <unistd.h>

static void	_configure_global_components()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	notimeout(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	srand(time(NULL));
	if(has_colors() == FALSE)
	{	
		endwin();
		write(2, "Your terminal does not support color\n", 37);
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
}

int	main(void)
{
	int 	x, y;
	int		center_x, center_y;
	t_game	game;

	_configure_global_components();
	
	getmaxyx(stdscr, y, x);
	center_x = x / 2;
	center_y = y / 2;

	WINDOW	*menuwin = subwin(stdscr, MENU_HEIGHT, MENU_WIDTH, center_y - MENU_HEIGHT - GAME_HEIGHT / 2, center_x - MENU_WIDTH / 2);
	WINDOW	*gamewin = subwin(stdscr, GAME_HEIGHT, GAME_WIDTH, center_y - GAME_HEIGHT / 2, center_x - GAME_WIDTH / 2);
	WINDOW	*pausewin = subwin(stdscr, PAUSE_HEIGHT, PAUSE_WIDTH, center_y - PAUSE_HEIGHT / 2, center_x - PAUSE_WIDTH / 2);
	WINDOW	*gameoverwin = subwin(stdscr, GAMEOVER_HEIGHT, GAMEOVER_WIDTH, center_y - GAMEOVER_HEIGHT / 2, center_x - GAMEOVER_WIDTH / 2);
	//TODO: look for failed allocation

	game_init(&game);
	while (game.status != OVER && game.status != STOPPED)
	{
		attron(COLOR_PAIR(1) | A_DIM);
		wprintw(stdscr, "+");
		attroff(COLOR_PAIR(1) | A_DIM);
		
		// handlers
		handle_input(&game);

		getmaxyx(gamewin, y, x);
		if (x < GAME_WIDTH)
			game.status = PAUSED;

		if (game.status != PAUSED)
			game_update(&game);
		menu_render(&game, menuwin);
		if (game.status != PAUSED)
			game_render(&game, gamewin);
		else
			pause_render(pausewin);
	}
	
	if (game.status == OVER)
	{
		nodelay(stdscr, FALSE);
		gameover_render(&game, gameoverwin);
		wgetch(stdscr);
	}

	delwin(menuwin);
	delwin(gamewin);
	delwin(pausewin);
	endwin();
	return (0);
}
