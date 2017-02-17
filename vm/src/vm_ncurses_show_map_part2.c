/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_show_map_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:19:35 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 17:19:36 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void			w_ft_displaybyte(WINDOW *win, int y, int x, unsigned char ptr)
{
	char 	result;
	char 	mod;

	result = ptr / 16;
	if (result < 10)
		result += '0';
	else
		result += 'a' - 10;
	mod = ptr % 16;
	if (mod < 10)
		mod += '0';
	else
		mod += 'a' - 10;
	mvwprintw(win, y,x, "%c%c", result, mod);
}

void			ncur_unhighlight_pc(WINDOW *win, t_map *tmap, t_proc *tproc,
									t_arena *tarena)
{
	unsigned int byte;
	int idx_cham;
	t_xy xy;

	xy.y = CONTENTS_START_Y + (tproc->pc / CONTENTS_BYTES_PER_LINE);
	xy.x = CONTENTS_START_X + ((tproc->pc % CONTENTS_BYTES_PER_LINE) * 3);
	idx_cham = tmap->possession[tproc->pc];
	byte = tmap->map[tproc->pc];
	if (idx_cham != -1)
	{
		wattron(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_BOLD);
		w_ft_displaybyte(win, xy.y, xy.x, byte);
		wattroff(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_BOLD);
	}
	else
	{
		wattron(win, COLOR_PAIR(7) | A_BOLD);
		w_ft_displaybyte(win, xy.y, xy.x, byte);
		wattroff(win, COLOR_PAIR(7) | A_BOLD);
	}
}

void			ncur_highlight_pc(WINDOW *win, t_map *tmap, t_proc *tproc,
									t_arena *tarena)
{
	unsigned int byte;
	int idx_cham;
	t_xy xy;

	xy.y = CONTENTS_START_Y + (tproc->pc / CONTENTS_BYTES_PER_LINE);
	xy.x = CONTENTS_START_X + ((tproc->pc % CONTENTS_BYTES_PER_LINE) * 3);
	idx_cham = tmap->possession[tproc->pc];
	byte = tmap->map[tproc->pc];
	if (idx_cham != -1)
	{
		wattron(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_STANDOUT);
		w_ft_displaybyte(win, xy.y, xy.x, byte);
		wattroff(win, COLOR_PAIR(tarena->tcham[idx_cham]->color) | A_STANDOUT);
	}
	else
	{
		wattron(win, COLOR_PAIR(7) | A_STANDOUT);
		w_ft_displaybyte(win, xy.y, xy.x, byte);
		wattroff(win, COLOR_PAIR(7) | A_STANDOUT);
	}
	wrefresh(win);
}

