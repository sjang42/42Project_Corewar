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
	wattron(win, COLOR_PAIR(7) | A_BOLD);
	wmove(win, TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN);
	while (i < 181)
	{
		waddch(win, ' ');
		i++;
	}
	wrefresh(win);
	wattroff(win, COLOR_PAIR(7) | A_BOLD);
}

void			ncur_show_termsays(WINDOW *win_arena)
{
	wattron(win_arena, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_arena, TERM_SAYS_Y, TERM_SAYS_X, TERM_SAYS_MASSAGE);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(7) | A_BOLD);
}

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
	mvwprintw(win_info, INFO_PROCESSES_Y, INFO_PROCESSES_X, "Processes : %d", num_process);
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

void			info_show_cycle_die_period(WINDOW *win_info, t_arena *tarena)
{
	int x;
	int y;

	x = INFO_CYCLE_DIE_X;
	y = INFO_NAME_CHAM1_Y + (4 * tarena->num_cham) + 2;
	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_info, y, x, "                               ");
	mvwprintw(win_info, y, x, "Period : %d",
				tarena->num_period + 1);
	y += 2;
	mvwprintw(win_info, y, x, "                               ");
	mvwprintw(win_info, y, x, "Cycle to die : %d",
				tarena->cycle_to_die);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			info_show_constants(WINDOW *win_info, t_arena *tarena)
{
	int x;
	int y;

	x = INFO_CYCLE_DIE_X;
	y = INFO_NAME_CHAM1_Y + (4 * tarena->num_cham) + 6;
	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_info, y, x, "                               ");
	mvwprintw(win_info, y, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	mvwprintw(win_info, y, x, "                               ");
	mvwprintw(win_info, y, x, "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win_info, y, x, "                               ");
	mvwprintw(win_info, y, x, "MAX_CHECKS : %d", NBR_LIVE);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}



void			info_show_cham_live_current(WINDOW *win_info, t_arena *tarena,
										int idx_cham)
{
	int x;
	int y;
	int i;
	int sum;

	wattron(win_info, COLOR_PAIR(7) | A_BOLD);
	// i = 0;
	// sum = 0;
	// while (i < tarena->tcham[idx_cham]->num_tproc)
	// {
	// 	sum += tarena->tcham[idx_cham]->tproc[i].period_live;
	// 	i++;
	// }
	x = INFO_NAME_NUM_X;
	y = INFO_NAME_CHAM1_Y + (4 * idx_cham) + 2;
	mvwprintw(win_info, y, x, "      ");
	mvwprintw(win_info, y, x, "%d", tarena->tcham[idx_cham]->current_live);
	wrefresh(win_info);
	wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
}

void			ncur_show_live(WINDOW *win_arena, t_arena *tarena,
				int idx_cham, int live_cham)
{
	static int idx = 0;

	ncur_erase_termsays(win_arena);
	if (idx >= 10)
		idx = 0;
	if (idx % 2 == 0)
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD);
	else
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	mvwprintw(win_arena,
			TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN,
			"A process shows that player %d is alive", live_cham);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	idx++;
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
		wattron(win_info, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win_info, y, x,
				"Player -%d : ", i + 1);
		wattron(win_info, COLOR_PAIR(tarena->tcham[i]->color) | A_BOLD);
		mvwprintw(win_info, y, x + 12,
				"%s", tarena->tcham[i]->theader.prog_name);
		wattroff(win_info, COLOR_PAIR(tarena->tcham[i]->color) | A_BOLD);
		wattron(win_info, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win_info, y + 1, x + 2,
				"Last Live : ");
		mvwprintw(win_info, y + 2, x + 2,
				"Lives in current period : ");
		mvwprintw(win_info, y + 1, INFO_NAME_NUM_X,
				"0");
		mvwprintw(win_info, y + 2, INFO_NAME_NUM_X,
				"0");
		wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
		i++;
		y += 4;
	}
	wrefresh(win_info);
}




















