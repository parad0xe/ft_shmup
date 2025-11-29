/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 08:28:18 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/29 08:30:30 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

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

typedef struct s_game_entity
{
	t_type	type;
	int 	position[2];
	char	*sprite;
	t_dir	direction;
}	t_game_entity;

#endif
