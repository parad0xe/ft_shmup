/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:58:05 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 14:49:17 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

static void	_render_entities(t_game *game, WINDOW *gamewin)
{
	t_entity current;
	
	for (int i = 0; i < BACKGROUND_ARRAY_SIZE; ++i)
	{
		current = game->board.background[i];
		int random_color = randint(4, 6);
		wattron(gamewin, COLOR_PAIR(random_color) | A_DIM);
		if(current.active)
			mvwaddch(gamewin, current.position.y, current.position.x, current.sprite);
		wattroff(gamewin, COLOR_PAIR(random_color) | A_DIM);
	}
	
	for (int i = 0; i < FRIENDS_ARRAY_SIZE; ++i)
	{
		current = game->board.friends[i];
		if(current.active)
			mvwaddch(gamewin, current.position.y, current.position.x, current.sprite);
	}
	for (int i = 0; i < ENEMIES_ARRAY_SIZE; ++i)
	{
		current = game->board.enemies[i];
		if(current.active)
		{
			if (current.type == ENEMY)
				wattron(gamewin, COLOR_PAIR(3) | A_BOLD);
			else if (current.type == ENEMY_LASER)
				wattron(gamewin, COLOR_PAIR(2) | A_BOLD);
			mvwaddch(gamewin, current.position.y, current.position.x, current.sprite);
			wattroff(gamewin, COLOR_PAIR(2) | A_BOLD | A_DIM);
		}
	}
}

void    game_render(t_game *game, WINDOW *gamewin)
{
	werase(gamewin);
	// wborder(gamewin, 0, 0, 0, 0, 0, 0, 0, 0);

	_render_entities(game, gamewin);

	mvwaddch(
		gamewin,
		game->player.position.y,
		game->player.position.x,
		game->player.sprite
	);
  
	wrefresh(gamewin);
}
