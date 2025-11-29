/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:28:18 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 20:24:41 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

# include <ncurses.h>
# include <sys/time.h>

# include <time.h>
# include <stdlib.h>

# define MENU_HEIGHT	3
# define GAME_HEIGHT	20
# define WIDTH			100

# define ENTITY_ARRAY_SIZE 100
# define BASE_HP 3




typedef enum e_type
{
	PLAYER = 0,
	ENEMY,
	PLAYER_LASER,
	ENEMY_LASER
}	t_type;

typedef enum e_game_status
{
	RUNNING = 0,
	PAUSED,
	OVER,
	STOPPED
}	t_game_status;

typedef enum e_pos_component
{
	ROW = 0,
	COL
}	t_pos_component;

typedef enum e_dir
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
}	t_dir;

typedef struct s_weapon
{
	char	sprite;
	int		bullet_speed;
	int		active;
	int		last_shoot_time;
}			t_weapon;

// TODO: implement this
typedef struct s_game_stat
{
	int			hp;
	size_t		n_kills;
	long long	start_time;
}	t_game_stat;

typedef struct s_game_entity
{
	t_type		type;
	t_weapon	weapon;
	char		sprite;
	int			position[2];
	int			direction[2];
	int			speed;
	int			active;
}	t_game_entity;

typedef struct s_board
{
	size_t			first_available_index;
	t_game_entity	board_array[ENTITY_ARRAY_SIZE];
}	t_board;

typedef struct s_game
{
	t_game_stat		stat;
	t_game_status	status;
	t_game_entity	player;
	t_board			board;
	double			fps;
	long long		fps_start_time;
	size_t			frame_counter;
}	t_game;

// init
void	init_enemy(t_game_entity enemy, size_t	index);
void	init_entity_array(t_board board);

// game
void	game_update(t_game *game);
void	game_render(t_game *game, WINDOW *gamewin);
void	game_init(t_game *game);

// render_utils
void	print_game_entities(t_game board, WINDOW *gamewin);

// entity
int	advance_entity(t_game_entity *entity);

// utils
long long	time_in_milliseconds(void);

// input
void	handle_input(t_game *game);

// ui
void	menu_render(t_game *game, WINDOW *menuwin);

#endif
