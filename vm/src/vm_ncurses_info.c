/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurse_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 02:06:07 by sjang             #+#    #+#             */
/*   Updated: 2017/02/09 02:06:08 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void			info_show_status(WINDOW *win_info, int stop)
{
	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_info, INFO_PAUSED_Y, INFO_PAUSED_X, "                ");
	if (stop)
	{
		mvwprintw(win_info, INFO_PAUSED_Y, INFO_PAUSED_X, "** PAUSED **");
	}
	else
	{
		mvwprintw(win_info, INFO_PAUSED_Y, INFO_PAUSED_X, "** RUNNING **");
	}
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			info_show_cycle(WINDOW *win_info, int cycle)
{
	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_info, INFO_CYCLE_Y, INFO_CYCLE_X, "Cycle : %d", cycle);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			info_show_process(WINDOW *win_info, int num_process)
{
	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_info, INFO_PROCESSES_Y,
				INFO_PROCESSES_X, "Processes : %d", num_process);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			info_show_cham_lastlive(WINDOW *win_info, t_arena *tarena,
										int idx_cham)
{
	int x;
	int y;

	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	x = INFO_NAME_NUM_X;
	y = INFO_NAME_CHAM1_Y + (4 * idx_cham) + 1;
	mvwprintw(win_info, y, x, "      ");
	mvwprintw(win_info, y, x, "%d", tarena->tcham[idx_cham]->last_live);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			info_show_cham_live_current(WINDOW *win_info, t_arena *tarena,
										int idx_cham)
{
	int x;
	int y;

	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	x = INFO_NAME_NUM_X;
	y = INFO_NAME_CHAM1_Y + (4 * idx_cham) + 2;
	mvwprintw(win_info, y, x, "      ");
	mvwprintw(win_info, y, x, "%d", tarena->tcham[idx_cham]->current_live);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}
