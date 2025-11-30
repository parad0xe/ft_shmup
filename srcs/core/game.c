/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:28:53 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 15:18:38 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

static t_entity *_find_available_slot(t_entity *array, size_t size)
{
	size_t	i;

	i = -1;
	// TODO: Improve performance by indexing the maximum unused index instead of iterating over the entire entity array.
	while (++i < size)
	{
		if (array[i].active == 0)
			return (&array[i]);
	}
	return (NULL);
}

void	game_init(t_game *game)
{
	game->status = RUNNING;
	game->last_frame_time = time_in_milliseconds();
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

void	enemy_shoot(t_game *game, t_entity *enemy)
{
	if (enemy->weapon.shooting_rate == 0)
		return ;
	if (game->frame_counter % enemy->weapon.shooting_rate == 0)
		if (randint(0, 100) < 5)
			game_shoot(game, *enemy, set_bullet1);
}

int	game_shoot(t_game *game, t_entity shooter, void (*set_bullet)(t_entity shooter, t_entity *bullet))
{
	t_entity	*slot;

	if (shooter.type == ENEMY)
		slot = _find_available_slot(game->board.enemies, ENEMIES_ARRAY_SIZE);
	else
		slot = _find_available_slot(game->board.friends, FRIENDS_ARRAY_SIZE);
	if (slot)
	{
		set_bullet(shooter, slot);
		game->board.entity_counter++;
		return (1);
	}
	return (0);
}

int	game_add_enemy(t_game *game)
{
	t_entity	*new;
	t_entity	*enemies;

	enemies = game->board.enemies;
	new = _find_available_slot(enemies, ENEMIES_ARRAY_SIZE);
	if (new)
	{
		set_enemy_badguy1(new);
		game->board.entity_counter++;
	}
	return (0);
}

int	game_add_background(t_game *game)
{
	t_entity	*new;
	t_entity	*background;

	background = game->board.background;
	new = _find_available_slot(background, BACKGROUND_ARRAY_SIZE);
	if (new)
	{
		set_background(new);
		game->board.entity_counter++;
	}
	return (0);
}

void	game_destroy_entity(t_game *game, t_entity *entity)
{
	if (entity->active)
	{
		entity->active = 0;
		game->board.entity_counter--;
	}
}

// TODO: put that elsewhere
int		is_out_of_box(t_entity *entity)
{
	if (entity->position.x >= 1 && entity->position.x <= GAME_WIDTH - 2)
		return (entity->position.y <= 0 || entity->position.y > GAME_HEIGHT- 1);
	return (TRUE);
}

/**
	* @brief updates the position of every game entity except player,
	* @brief then renders the game on screen.
	* @brief also generates a wave every X frames,
	* @brief and makes every enemy shoot every Y frames
*/
void	game_update(t_game *game)
{
	t_entity *enemies;
	t_entity *friends;
	t_entity *background;

	enemies = game->board.enemies;
	friends = game->board.friends;
	background = game->board.background;

	++game->frame_counter;
	// TODO: Improve performance by indexing the maximum unused index instead of iterating over the entire entity array.

	if (game->stat.hp == 0)
	{
		game->status = OVER;
		return ;
	}

	if (TIME_BETWEEN_WAVES / MAX_FPS == 0 && randint(0, 100) < 7)
		game_add_enemy(game);

	// FOR EACH FRIEND

	for (int i = 0; i < FRIENDS_ARRAY_SIZE; ++i)
	{
		if (friends[i].active == 0)
			continue ;
		else if (friends[i].speed == 0)
			continue ;
		if (game->frame_counter % friends[i].speed == 0)
			entity_advance(&friends[i]);
		if (is_out_of_box(&friends[i]))
			game_destroy_entity(game, &friends[i]);
	}

	for (int i = 0; i < BACKGROUND_ARRAY_SIZE; ++i)
	{
		if (randfloat(0, 1) < 0.0005)
			game_add_background(game);
		
		if (background[i].active == 0)
			continue ;
		else if (background[i].speed == 0)
			continue ;
		if (game->frame_counter % background[i].speed == 0)
			entity_advance(&background[i]);
		if (is_out_of_box(&background[i]))
			game_destroy_entity(game, &background[i]);
	}

	// FOR EACH ENEMY
	// every friendly entity just advanced.
	// Check for collisions with updated friends and then advance.

	for (int i = 0; i < ENEMIES_ARRAY_SIZE; ++i)
	{
		if (enemies[i].active == 0)
			continue ;
		else if (enemies[i].speed == 0)
			continue ;

		// shoot probability for enemy
		// if (enemies[i].type == ENEMY && randfloat(0, 1) < 0.005)
		enemy_shoot(game, &enemies[i]);

		// check collision between player and the entity
		if (entity_check_collision(game->player, enemies[i]))
		{
			if (enemies[i].type == ENEMY)
			{
				game->status = OVER;
				return ;
			}
			else
		{
				game_destroy_entity(game, &game->board.enemies[i]);
				game->stat.hp--;
			}
		}
		else
	{
			// check collision between any friend and the entity
			for (int j = 0; j < FRIENDS_ARRAY_SIZE; ++j)
			{
				if (entity_check_collision(enemies[i], friends[j]))
				{
					if (enemies[i].type == ENEMY)
						game->stat.n_kills++;
					game_destroy_entity(game, &enemies[i]);
					game_destroy_entity(game, &friends[j]);
					break ;
				}
			}
		}
		if (game->frame_counter % enemies[i].speed == 0)
		{
			entity_advance(&enemies[i]);
			if (is_out_of_box(&enemies[i]))
			{
				--game->stat.hp;
				game_destroy_entity(game, &enemies[i]);
			}

		}
		if (is_out_of_box(&enemies[i]))
			game_destroy_entity(game, &enemies[i]);
	}
	while ((time_in_milliseconds() - game->last_frame_time) <= 1000 * (1. / (MAX_FPS)))
		usleep(500);
	game->last_frame_time = time_in_milliseconds();
}
