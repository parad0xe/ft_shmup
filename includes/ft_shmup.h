/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:28:18 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 11:27:43 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

# define ENTITY_ARRAY_SIZE 100

#include <ncurses.h>
#include <sys/time.h>

typedef enum e_type
{
	PLAYER = 0,
	ENEMY,
	LASER
}	t_type;

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

typedef struct s_framerate
{
	long long	time_prev;
	long long	time_current;
	long long	time_elapsed;
	long long	time_prev_fps;
	double		delta;
	double		accumulator;
	int			fps_counter;
	int			fps_display;
}	t_framerate;

typedef struct s_game_entity
{
	char	symbol;
	t_type	type;
	char	*sprite;
	int		position[2];
	int		direction;
	int		active;
}	t_game_entity;

typedef struct s_board
{
	size_t			first_available_index;
	t_game_entity	board_array[ENTITY_ARRAY_SIZE];
}	t_board;

typedef struct s_game
{
	int				is_over;
	t_game_entity	player;
	t_framerate		framerate;
	t_board			board;
	WINDOW			*menu_win;
	WINDOW			*game_win;
}	t_game;

// game
void	game_update_framerate(t_game *game);
void	game_update(t_game *game);
void	game_render(t_game *game);

void	print_game_entities(t_game board);

// utils
long long	timeInMilliseconds(void);

#endif
