/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:11:54 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 09:05:08 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <ncurses.h>
#include <time.h>

#include <unistd.h>
int	main(void)
{
	int width = 300;
	int height = 300;
	int row = 0;
	int col = 0;

	initscr();
	cbreak();
	noecho();
	WINDOW *win = newwin(height, width, row, col);
	int ch = getch();
	(void)ch;
	mvwprintw(win, 7, 0, "You pressed the up arrow key");
	sleep(1);
	endwin();
	return (0);
}
