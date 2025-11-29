/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:31:10 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/29 19:46:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	print_game_entities(t_game game, WINDOW *gamewin)
{
	t_game_entity current;

	for (int i = 0; i < ENTITY_ARRAY_SIZE; ++i)
	{
		current = game.board.board_array[i];
		if(current.active)
			mvwprintw(gamewin, current.position[ROW], current.position[COL], "%c", 'a');
	}
}

