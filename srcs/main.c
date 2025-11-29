/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 22:18:36 by nlallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <ncurses.h>



int	main(void)
{
	t_game	game;

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	notimeout(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	srand(time(NULL));

	WINDOW	*menuwin = subwin(stdscr, MENU_HEIGHT, MENU_WIDTH, 0, 0);
	WINDOW	*gamewin = subwin(stdscr, GAME_HEIGHT, GAME_WIDTH, 4, 0);
	WINDOW	*pausewin = subwin(stdscr, PAUSE_HEIGHT, PAUSE_WIDTH, GAME_HEIGHT/2, GAME_WIDTH/2 - PAUSE_WIDTH/2);
	//TODO: look for failed allocation


	game_init(&game);
	while (game.status != OVER && game.status != STOPPED)
	{
		// handlers
		handle_input(&game);
		if (game.status != PAUSED)
			game_update(&game);
		menu_render(&game, menuwin);
		if (game.status != PAUSED)
			game_render(&game, gamewin);
		else
			pause_render(pausewin);
	}

	delwin(menuwin);
	delwin(gamewin);
	delwin(pausewin);
	endwin();
	return (0);
}
