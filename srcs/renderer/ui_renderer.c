/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_renderer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:53:03 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/30 14:51:44 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

void	gameover_render(t_game *game, WINDOW *gameoverwin)
{
	size_t		score = 0;
	long long	cur_time = time_in_milliseconds() - game->stat.start_time;

	score = game->stat.n_kills * 100;
	werase(gameoverwin);
	wborder(gameoverwin, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(gameoverwin, 1, GAMEOVER_WIDTH - GAMEOVER_WIDTH / 2 - 4, "GAME OVER");
	mvwprintw(gameoverwin, 3, 2, "score: %zu", score);
	mvwprintw(gameoverwin, 3, 18, "kills: %-4u", game->stat.n_kills);
	mvwprintw(gameoverwin, 3, 32, "time: %lld:%02lld", cur_time / 60000, (cur_time / 1000) % 60);
	wrefresh(gameoverwin);
}

void	pause_render(WINDOW *pausewin)
{
	wborder(pausewin, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(pausewin, PAUSE_HEIGHT - PAUSE_HEIGHT / 2 - 1, PAUSE_WIDTH - PAUSE_WIDTH / 2 - 3, "PAUSED");
	wrefresh(pausewin);
}

void	menu_render(t_game *game, WINDOW *menuwin)
{
	long long	current_timestamp = time_in_milliseconds();
	long long	cur_time = current_timestamp - game->stat.start_time;
	size_t		score = game->stat.n_kills * 100;

	if (current_timestamp - game->fps_start_time >= 1000.)
	{
		game->fps = game->frame_counter;
		game->frame_counter = 1;
		game->fps_start_time = current_timestamp;
	}
	werase(menuwin);
	mvwprintw(menuwin, 10, 20, "fps: %-7.2f", game->fps);
	mvwprintw(menuwin, 10, 40, "score: %zu", score);
	mvwprintw(menuwin, 10, 60, "HP: %u", game->stat.hp);
	mvwprintw(menuwin, 12, 20, "entities: %-4d", game->board.entity_counter);
	mvwprintw(menuwin, 12, 40, "kills: %-4u", game->stat.n_kills);
	mvwprintw(menuwin, 12, 60, "time: %lld:%02lld", cur_time / 60000, (cur_time / 1000) % 60);
	mvwaddstr(menuwin, 1, MENU_WIDTH / 2 - 43 / 2, SWAG1);
	mvwaddstr(menuwin, 2, MENU_WIDTH / 2 - 43 / 2, SWAG2);
	mvwaddstr(menuwin, 3, MENU_WIDTH / 2 - 43 / 2, SWAG3);
	mvwaddstr(menuwin, 4, MENU_WIDTH / 2 - 43 / 2, SWAG4);
	mvwaddstr(menuwin, 5, MENU_WIDTH / 2 - 43 / 2, SWAG5);
	mvwaddstr(menuwin, 6, MENU_WIDTH / 2 - 43 / 2, SWAG6);
	mvwaddstr(menuwin, 7, MENU_WIDTH / 2 - 43 / 2, SWAG7);
	mvwaddstr(menuwin, 8, MENU_WIDTH / 2 - 43 / 2, SWAG8);
	mvwaddstr(menuwin, 9, 0, "\n");
	wrefresh(menuwin);
}
