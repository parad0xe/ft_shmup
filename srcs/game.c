/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 19:46:28 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	game_init(t_game *game)
{
	game->status= RUNNING;
	game->stat = (t_game_stat){
		.hp = BASE_HP,
		.n_kills = 0,
		.start_time = time_in_milliseconds()
	};
	game->board = (t_board){0};
	game->player = (t_game_entity){
			.sprite = '>',
			.type = PLAYER,
			.weapon = {
				.active = 1,
				.sprite = '-',
				.bullet_speed = 3,
				.last_shoot_time = 0.
			},
			.position = { 1, GAME_HEIGHT / 2  },
			.direction = {0, 0},
			.speed = 0,
		};
	game->fps_start_time = time_in_milliseconds();
	game->fps = 0.;
	game->frame_counter = 0;
}

/** 
	* @brief updates the position of every game entity except player,
	* @brief then renders the game on screen.
	* @brief also generates a wave every X frames,
	* @brief and makes every enemy shoot every Y frames
*/
void	game_update(t_game *game)
{
	t_game_entity *entities;


	entities = game->board.board_array;
	++game->frame_counter;
	for (int i = 0; i < ENTITY_ARRAY_SIZE; ++i)
	{
		if (entities[i].active == FALSE)
			continue ;
		else if (entities[i].speed == 0)
			continue ;
		if (game->frame_counter % entities[i].speed == 0)
			advance_entity(&entities[i]);
	}
}

void    game_render(t_game *game, WINDOW *gamewin)
{
	werase(gamewin);
	wborder(gamewin, 0, 0, 0, 0, 0, 0, 0, 0);

	mvwprintw(
		gamewin,
		game->player.position[ROW],
		game->player.position[COL],
		"%c",
		game->player.sprite
	);
	print_game_entities(*game, gamewin);

	wrefresh(gamewin);
}
