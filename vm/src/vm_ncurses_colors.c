/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 00:21:22 by sjang             #+#    #+#             */
/*   Updated: 2017/02/08 00:21:23 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void		colors_init(WINDOW *win)
{
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);
	wrefresh(win);
}

int			colors_set_pc(WINDOW *win, t_arena *tarena, int pc)
{
	int idx_cham;

	idx_cham = tarena->tmap->possession[pc];
	if (idx_cham != -1)
	{
		wattron(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_BOLD);
	}
	else
	{
		wattron(win, COLOR_PAIR(7) | A_BOLD);
	}
	return (idx_cham);
}

int			colors_off_pc(WINDOW *win, t_arena *tarena, int pc)
{
	int idx_cham;

	idx_cham = tarena->tmap->possession[pc];
	if (idx_cham != -1)
	{
		wattroff(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_BOLD);
	}
	else
	{
		wattroff(win, COLOR_PAIR(7) | A_BOLD);
	}
	return (idx_cham);
}
