/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:57:29 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 01:29:48 by nlallema         ###   ########lyon.fr   */
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
			if (game->player.position.y - 1 > 0)
				game->player.position.y -= 1;
			break ;
		case KEY_DOWN:
			if (game->player.position.y + 1 < GAME_HEIGHT - 1)
				game->player.position.y += 1;
			break ;
		case KEY_LEFT:
			if (game->player.position.x - 1 > 0)
				game->player.position.x -= 1;
			break ;
		case KEY_RIGHT:
			if (game->player.position.x + 1 < GAME_WIDTH - 1)
				game->player.position.x += 1;
			break ;
		case 'e':
			game_add_entity(game, &set_enemy_badguy1);
			break ;
		case ' ':
			game_shoot(game, game->player, &set_bullet1);
			break ;
	}
}

void	handle_input(t_game *game)
{
	int ch;

	ch = wgetch(stdscr);
	switch (ch)
	{
		case 'q':
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


