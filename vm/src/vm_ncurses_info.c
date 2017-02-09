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

void			ncur_erase_termsays(WINDOW *win)
{
	int i;

	i = 0;
	wmove(win, TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN);
	while (i < 181)
	{
		waddch(win, ' ');
		i++;
	}
}

void			ncur_show_termsays(WINDOW *win_arena)
{
	mvwprintw(win_arena, TERM_SAYS_Y, TERM_SAYS_X, TERM_SAYS_MASSAGE);
}

void			info_show_status(WINDOW *win_info, int stop)
{
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
}

void			info_show_cycle(WINDOW *win_info, int cycle)
{
	mvwprintw(win_info, INFO_CYCLE_Y, INFO_CYCLE_X, "Cycle : %d", cycle);
	wrefresh(win_info);
}

void			info_show_process(WINDOW *win_info, int num_process)
{
	mvwprintw(win_info, INFO_PROCESSES_Y, INFO_PROCESSES_X, "Processes : %d", num_process);
	wrefresh(win_info);
}

void			info_show_cham_lastlive(WINDOW *win_info, t_arena *tarena,
										int idx_cham)
{
	int x;
	int y;

	x = INFO_NAME_NUM_X;
	y = INFO_NAME_CHAM1_Y + (4 * idx_cham) + 1;
	mvwprintw(win_info, y, x, "      ");
	mvwprintw(win_info, y, x, "%d", tarena->tcham[idx_cham]->last_live);
}

void			info_show_cham_live_current(WINDOW *win_info, t_arena *tarena,
										int idx_cham)
{
	int x;
	int y;
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (i < tarena->tcham[idx_cham]->num_tproc)
	{
		sum += tarena->tcham[idx_cham]->tproc[i].period_live;
		i++;
	}
	x = INFO_NAME_NUM_X;
	y = INFO_NAME_CHAM1_Y + (4 * idx_cham) + 2;
	mvwprintw(win_info, y, x, "      ");
	mvwprintw(win_info, y, x, "%d", sum);
}

void			info_show_cham_init(WINDOW *win_info, t_arena *tarena)
{
	int i;
	int x;
	int y;

	i = 0;
	x = INFO_NAME_CHAM1_X;
	y = INFO_NAME_CHAM1_Y;
	while (i < tarena->num_cham)
	{
		mvwprintw(win_info, y, x,
				"Player -%d : ", i + 1);
		attron(COLOR_PAIR(i) | A_BOLD);
		mvwprintw(win_info, y, x + 12,
				"%s", tarena->tcham[i]->tfile.fname);
		mvwprintw(win_info, y + 1, x + 2,
				"Last Live : ");
		mvwprintw(win_info, y + 2, x + 2,
				"Lives in current period : ");
		mvwprintw(win_info, y + 1, INFO_NAME_NUM_X,
				"0");
		mvwprintw(win_info, y + 2, INFO_NAME_NUM_X,
				"0");
		attroff(COLOR_PAIR(i) | A_BOLD);
		i++;
		y += 4;
	}
	wrefresh(win_info);
}




















