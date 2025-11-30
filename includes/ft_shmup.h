/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:28:18 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 03:17:49 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

// == INCLUDES

# include <ncurses.h>
# include <sys/time.h>

# include <time.h>
# include <stdlib.h>

// == MACROS

# define MAX_WIDTH 			90

# define MENU_HEIGHT		5
# define MENU_WIDTH			MAX_WIDTH

# define GAME_HEIGHT		20
# define GAME_WIDTH			MAX_WIDTH

# define PAUSE_HEIGHT		GAME_HEIGHT/3
# define PAUSE_WIDTH		GAME_WIDTH/3

# define GAMEOVER_HEIGHT	GAME_HEIGHT/3
# define GAMEOVER_WIDTH		GAME_WIDTH/2


# define ENEMIES_ARRAY_SIZE 100
# define FRIENDS_ARRAY_SIZE 30
# define BASE_HP 300


// === ENUMS ==

typedef enum e_entity_type
{
	PLAYER = 0,
	ENEMY,
	PLAYER_LASER,
	ENEMY_LASER
}	t_entity_type;

typedef enum e_game_status
{
	RUNNING = 0,
	PAUSED,
	OVER,
	STOPPED
}	t_game_status;

typedef enum e_dir
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
}	t_dir;

// == STRUCTS ==

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

typedef struct s_weapon
{
	char	sprite;
	int		speed;
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

typedef struct s_entity
{
	t_entity_type	type;
	t_weapon		weapon;
	char			sprite;
	t_xy			position;
	t_xy			direction;
	int				speed;
	int				active;
}	t_entity;

typedef struct s_board
{
	size_t		first_available_index;
	t_entity	enemies[ENEMIES_ARRAY_SIZE];
	t_entity	friends[FRIENDS_ARRAY_SIZE];
	int			entity_counter;
}	t_board;

typedef struct s_game
{
	t_game_stat		stat;
	t_game_status	status;
	t_entity		player;
	t_board			board;
	double			fps;
	long long		fps_start_time;
	size_t			frame_counter;
}	t_game;

// == PROTOTYPES

// game
void		game_init(t_game *game);
int			game_shoot(t_game *game, t_entity shooter, void (*set_bullet)(t_entity shooter, t_entity *bullet));
// int			game_add_entity(t_entity *entity_array, size_t slot, void (*set_entity)(t_entity *entity));
int			game_add_enemy(t_game *game);
void		game_update(t_game *game);

// entity
int			entity_advance(t_entity *entity);
int			entity_check_collision(t_entity entity, t_entity other);
void		entity_set_weapon(t_entity *entity, char sprite, int speed);

// input
void		handle_input(t_game *game);

// enenmy
void		set_enemy_badguy1(t_entity *entity);

// player
void		set_player1(t_entity *player);

// bullet
void		set_bullet1(t_entity shooter, t_entity *bullet);

// game_renderer
void		game_render(t_game *game, WINDOW *gamewin);

// ui_renderer
void		gameover_render(t_game *game, WINDOW *gameoverwin);
void		menu_render(t_game *game, WINDOW *menuwin);
void		pause_render(WINDOW *pausewin);

// time_utils
long long	time_in_milliseconds(void);

// rand_utils
int			randint(int min, int max);
double		randfloat(int min, int max);

#endif
