/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:57:29 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 16:44:42 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "ft_shmup.h"
#include "core.h"

static void	_handle_input_player(t_game *game, int ch)
{
	if (game->status == PAUSED)
		return ;
	switch (ch)
	{
		case 'w':
			game_update_player_position(game, 0, -1);
			break ;
		case 's':
			game_update_player_position(game, 0, 1);
			break ;
		case 'a':
			game_update_player_position(game, -1, 0);
			break ;
		case 'd':
			game_update_player_position(game, 1, 0);
			break ;
		case 'e':
			game_add_enemy(game);
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
		case 'r':
			if (game->status == OVER)
				game->status = RUNNING;
			break ;
		default:
			_handle_input_player(game, ch);
	}
}
