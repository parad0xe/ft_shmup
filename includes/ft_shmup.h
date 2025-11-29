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

#include <ncurses.h>
#include <sys/time.h>

typedef enum e_type
{
	PLAYER = 0,
	ENNEMY,
	LASER
}	t_type;

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
	int		posititon[2];
	int		direction[2];
}	t_game_entity;

typedef struct s_game
{
	int				is_over;
	t_game_entity	player;
	t_framerate		framerate;
}	t_game;

// game
void	game_update_framerate(t_game *game);
void	game_update(t_game *game);
void	game_render(t_game *game);

// utils
long long	timeInMilliseconds(void);

#endif
