/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:57:29 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/29 19:47:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include "ncurses.h"

static void	_handle_input_player(t_game *game, int ch)
{
	if (game->status == PAUSED)
		return ;
	switch (ch)
	{
		case KEY_UP:
			if (game->player.position[ROW] - 1 > 0)
				game->player.position[ROW] -= 1;
			break ;
		case KEY_DOWN:
			if (game->player.position[ROW] + 1 < GAME_HEIGHT - 1)
				game->player.position[ROW] += 1;
			break ;
		case KEY_LEFT:
			if (game->player.position[COL] - 1 > 0)
				game->player.position[COL] -= 1;
			break ;
		case KEY_RIGHT:
			if (game->player.position[COL] + 1 < WIDTH - 1)
				game->player.position[COL] += 1;
	}
}

void	handle_input(t_game *game)
{
	int ch;

	ch = wgetch(stdscr);
	switch (ch)
	{
		case 113:
			game->status = STOPPED;
			break ;
		case 'p':
			if (game->status == PAUSED)
				game->status = RUNNING;
			else if (game->status == RUNNING)
				game->status = PAUSED;
			break ;
		default:
			_handle_input_player(game, ch);
	}
}


