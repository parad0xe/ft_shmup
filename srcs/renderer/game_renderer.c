/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:58:05 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 00:43:24 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

static void	_render_entities(t_game *game, WINDOW *gamewin)
{
	t_entity current;

	for (int i = 0; i < ENTITY_ARRAY_SIZE; ++i)
	{
		current = game->board.entities[i];
		if(current.active)
			mvwprintw(gamewin, current.position.y, current.position.x, "%c", current.sprite);
	}
}

void    game_render(t_game *game, WINDOW *gamewin)
{
	werase(gamewin);
	wborder(gamewin, 0, 0, 0, 0, 0, 0, 0, 0);

	mvwprintw(
		gamewin,
		game->player.position.y,
		game->player.position.x,
		"%c",
		game->player.sprite
	);
	
	_render_entities(game, gamewin);

	wrefresh(gamewin);
}