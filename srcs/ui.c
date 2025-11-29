/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:53:03 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/29 22:17:48 by nlallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

// TODO: add Pause and Game Over windows
void	pause_render(WINDOW *pausewin)
{
	wborder(pausewin, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(pausewin, PAUSE_HEIGHT-PAUSE_HEIGHT/2-1, PAUSE_WIDTH-PAUSE_WIDTH/2-3, "PAUSED");
	wrefresh(pausewin);
}

void	menu_render(t_game *game, WINDOW *menuwin)
{
	size_t	score = 0;
	long long cur_time = time_in_milliseconds() - game->stat.start_time;

	score = game->stat.n_kills * 100;

	if (time_in_milliseconds() - game->fps_start_time >= 1000.)
	{
		game->fps = game->frame_counter;
		game->frame_counter = 0;
		game->fps_start_time = time_in_milliseconds();
	}
	
	wborder(menuwin, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(menuwin, 1, 10, "fps: %-10.0f", game->fps);
	mvwprintw(menuwin, 1, 30, "score: %zu", score);
	mvwprintw(menuwin, 1, 50, "HP: %d", game->stat.hp);
	mvwprintw(menuwin, 1, 70, "time: %lld:%02lld", cur_time / 60000, (cur_time / 1000) % 60);
	wrefresh(menuwin);
}
