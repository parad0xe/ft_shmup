/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 03:13:42 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

static t_entity*	_find_available_slot(t_game *game)
{
	int	i;

	i = -1;
	// TODO: Improve performance by indexing the maximum unused index instead of iterating over the entire entity array.
	while (++i < ENTITY_ARRAY_SIZE)
	{
		if (game->board.entities[i].active == 0)
			return (&game->board.entities[i]);
	}
	return (0);
}

void	game_init(t_game *game)
{
	game->status= RUNNING;
	game->stat = (t_game_stat){
		.hp = BASE_HP,
		.n_kills = 0,
		.start_time = time_in_milliseconds()
	};
	game->board = (t_board){0};
	game->fps_start_time = time_in_milliseconds();
	game->fps = 0.;
	game->frame_counter = 0;
	
	set_player1(&game->player);
}

int	game_shoot(t_game *game, t_entity shooter, void (*set_bullet)(t_entity shooter, t_entity *bullet))
{
	t_entity	*slot;
	
	slot = _find_available_slot(game);
	if (slot)
	{
		set_bullet(shooter, slot);
		game->board.entity_counter++;
		return (1);
	}
	return (0);
}

int	game_add_entity(t_game *game, void (*set_entity)(t_entity *entity))
{
	t_entity	*slot;
	
	slot = _find_available_slot(game);
	if (slot)
	{
		set_entity(slot);
		game->board.entity_counter++;
		return (1);
	}
	return (0);
}

void	game_destroy_entity(t_game *game, t_entity *entity)
{
	entity->active = 0;
	game->board.entity_counter--;
}

/** 
	* @brief updates the position of every game entity except player,
	* @brief then renders the game on screen.
	* @brief also generates a wave every X frames,
	* @brief and makes every enemy shoot every Y frames
*/
void	game_update(t_game *game)
{
	t_entity *entities;

	entities = game->board.entities;
	++game->frame_counter;
	// TODO: Improve performance by indexing the maximum unused index instead of iterating over the entire entity array.
	for (int i = 0; i < ENTITY_ARRAY_SIZE; ++i)
	{
		if (game->stat.hp == 0)
		{
			game->status = OVER;
			return ;
		}
		if (entities[i].active == 0)
			continue ;
		else if (entities[i].speed == 0)
			continue ;
		if (game->frame_counter % entities[i].speed == 0)
			entity_advance(&entities[i]);
		
		// shoot probability for enemy
		if (entities[i].type == ENEMY && randfloat(0, 30000) < 0.1)
			game_shoot(game, entities[i], &set_bullet1);

		// check collision between player and (enemy, enemy_laser)
		if (entities[i].type != PLAYER_LASER && entity_check_collision(game->player, entities[i]))
		{
			if (entities[i].type == ENEMY)
			{
				game->status = OVER;
				return ;
			}
			else if (entities[i].type == ENEMY_LASER)
			{
				game_destroy_entity(game, &game->board.entities[i]);
				game->stat.hp--;
			}
		}
		else
		{
			// check collision between player_laser and (enemy, enemy_laser)
			for (int j = 0; j < ENTITY_ARRAY_SIZE; ++j)
			{
				if (entities[i].type == PLAYER_LASER && entities[j].type != PLAYER_LASER && entity_check_collision(entities[i], entities[j]))
				{
					if (entities[j].type == ENEMY)
						game->stat.n_kills++;
					game_destroy_entity(game, &game->board.entities[i]);
					game_destroy_entity(game, &game->board.entities[j]);
					break ;
				}
				else if (entities[i].type != PLAYER_LASER && entities[j].type == PLAYER_LASER && entity_check_collision(entities[i], entities[j]))
				{
					if (entities[i].type == ENEMY)
						game->stat.n_kills++;
					game_destroy_entity(game, &game->board.entities[i]);
					game_destroy_entity(game, &game->board.entities[j]);
					break ;
				}
			}
		}
		// check if entity is out of the box
		if (entities[i].active)
		{
			if (entities[i].position.x <= 0 || entities[i].position.x > GAME_WIDTH - 1)
			{
				// Check whether an enemy has reached the player's base
				if (entities[i].type == ENEMY)
					game->stat.hp--;
				game_destroy_entity(game, &game->board.entities[i]);
			}
			else if (entities[i].position.y <= 0 || entities[i].position.y > GAME_HEIGHT - 1)
				game_destroy_entity(game, &game->board.entities[i]);
		}
	}
}
