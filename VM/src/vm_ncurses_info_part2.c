/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_info_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:12:57 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 17:12:59 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void		info_show_cycle_die_period(WINDOW *win_info, t_arena *tarena)
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

void		info_show_constants(WINDOW *win_info, t_arena *tarena)
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

void		info_show_cham_init(WINDOW *win_info, t_arena *tarena)
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
		mvwprintw(win_info, y, x, "Player -%d : ", i + 1);
		wattron(win_info, COLOR_PAIR(tarena->tcham[i]->color) | A_BOLD);
		mvwprintw(win_info, y, x + 12, "%s",
					tarena->tcham[i]->theader.prog_name);
		wattroff(win_info, COLOR_PAIR(tarena->tcham[i]->color) | A_BOLD);
		wattron(win_info, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win_info, y + 1, x + 2, "Last Live : ");
		mvwprintw(win_info, y + 2, x + 2, "Lives in current period : ");
		mvwprintw(win_info, y + 1, INFO_NAME_NUM_X, "0");
		mvwprintw(win_info, y + 2, INFO_NAME_NUM_X, "0");
		wattroff(win_info, COLOR_PAIR(7) | A_BOLD);
		i++;
		y += 4;
	}
	wrefresh(win_info);
}
