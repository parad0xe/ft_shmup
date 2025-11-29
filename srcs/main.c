/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 20:10:59 by kbarru           ###   ########lyon.fr   */
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

	WINDOW	*menuwin = subwin(stdscr, MENU_HEIGHT, WIDTH, 0, 0);
	WINDOW	*gamewin = subwin(stdscr, GAME_HEIGHT, WIDTH, 4, 0);
	//TODO: look for failed allocation


	game_init(&game);
	while (game.status != OVER && game.status != STOPPED)
	{
		// handlers
		handle_input(&game);
		if (game.status != PAUSED)
			game_update(&game);
		menu_render(&game, menuwin);
		game_render(&game, gamewin);
	}

	delwin(menuwin);
	delwin(gamewin);
	delwin(stdscr);
	endwin();
	return (0);
}
