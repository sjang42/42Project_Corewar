/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_arena_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:11:49 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 17:11:50 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

static void		ncur_erase_aff(WINDOW *win)
{
	int i;

	i = 0;
	wattron(win, COLOR_PAIR(7) | A_BOLD);
	wmove(win, AFF_Y, AFF_X + AFF_MASSAGE_LEN);
	while (i < 181)
	{
		wprintw(win, " ");
		i++;
	}
	wrefresh(win);
	wattroff(win, COLOR_PAIR(7) | A_BOLD);
}

void			ncur_show_aff(WINDOW *win_arena, int idx_cham, char byte)
{
	static int idx = 0;

	ncur_erase_aff(win_arena);
	if (idx >= 10)
		idx = 0;
	wattron(win_arena, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_arena, AFF_Y, AFF_X, "AFF : ", byte);
	wattroff(win_arena, COLOR_PAIR(7) | A_BOLD);
	if (idx % 2 == 0)
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD);
	else
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	mvwprintw(win_arena, AFF_Y, AFF_X + AFF_MASSAGE_LEN, "%c", byte);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	idx++;
}
