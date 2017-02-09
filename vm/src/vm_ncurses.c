/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 23:41:35 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 23:41:36 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void	draw_repeat_ch_hor(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x, y + i);
		waddch(win, ch);
		i++;
	}
}

void	draw_repeat_ch_ver(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x + i, y);
		waddch(win, ch);
		i++;
	}
}

void	ncur_finish(t_windows *twin)
{
	delwin(twin->win_arena);
	delwin(twin->win_info);
	endwin();
}



void		t_arena_destroy(t_arena *tarena)
{
	int idx_cham;

	idx_cham = 0;
	t_map_destroy(tarena->tmap);
	while (idx_cham < tarena->num_cham)
	{
		t_champion_destroy(tarena->tcham[idx_cham]);
		idx_cham++;
	}
	free(tarena->tcham);
	free(tarena);
}































// void	ncur_box(WINDOW *win)
// {
// 	attrset(COLOR_PAIR(8) | A_BOLD);
// 	draw_repeat_ch_hor(win, '*', TOTAL_COLS, DIVIDE_HOR_FIRST, 0);
// 	draw_repeat_ch_hor(win, '*', TOTAL_COLS, DIVIDE_HOR_SECOND, 0);
// 	draw_repeat_ch_ver(win, '*', TOTAL_LINES - 2, 1, DIVIDE_VER_FIRST);
// 	draw_repeat_ch_ver(win, '*', TOTAL_LINES - 2, 1, DIVIDE_VER_SECOND);
// 	draw_repeat_ch_ver(win, '*', TOTAL_LINES - 2, 1, DIVIDE_VER_THIRD);
// 	attrset(COLOR_PAIR(7));
// }
