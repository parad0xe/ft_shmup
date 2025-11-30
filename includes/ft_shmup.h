/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:28:18 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 17:00:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

// == INCLUDES

# include <ncurses.h>
# include <sys/time.h>

# include <time.h>
# include <stdlib.h>

# include <unistd.h>

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

# define MAX_FPS			60

# define TIME_BETWEEN_WAVES 36
# define ENEMIES_ARRAY_SIZE 100
# define FRIENDS_ARRAY_SIZE 30

# define BACKGROUND_ARRAY_SIZE 100
# define BASE_HP 10

# define DEFAULT_ENEMY_SPEED	240
# define DEFAULT_BULLET_SPEED	160
# define DEFAULT_SHOOTING_RATE	720

# define MEMORY_ERROR_MSG "Memory allocation failed\n"
# define ERR_NOCOLORS "Your terminal does not support color\n"
# define ERR_RESIZED "Terminal was resized\n"

// === ENUMS ==

typedef enum e_entity_type
{
	PLAYER = 0,
	ENEMY,
	PLAYER_LASER,
	ENEMY_LASER,
	BACKGROUND
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
	int		shooting_rate;
}			t_weapon;

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
	t_entity	background[BACKGROUND_ARRAY_SIZE];
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
	long long		last_frame_time;
	size_t			frame_counter;
}	t_game;

typedef struct s_windows
{
	WINDOW	*gamewin;
	WINDOW	*menuwin;
	WINDOW	*pausewin;
	WINDOW	*gameoverwin;
}	t_windows;
// input
void		handle_input(t_game *game);

// enenmy
void		set_enemy_badguy1(t_entity *entity);

// player
void		set_player1(t_entity *player);

// bullet
void		set_bullet1(t_entity shooter, t_entity *bullet);

// background
void		set_background(t_entity *slot);

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
