/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_show_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 23:45:43 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 23:45:44 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void		w_ft_displaybyte(WINDOW *win, int y, int x, unsigned char ptr)
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
	wmove(win, y, x);
	waddch(win, result);
	waddch(win, mod);
}

void			ncur_map_init(WINDOW *win, t_map *tmap, t_arena *tarena)
{
	size_t			i;
	size_t			j;
	int				pc;
	t_xy 			idx;
	unsigned char	*ptr;

	idx.x = CONTENTS_START_X;
	idx.y = CONTENTS_START_Y;
	pc = 0;
	colors_init(win);
	while (pc < tmap->size_map)
	{
		colors_set_pc(win, tarena, pc);
		w_ft_displaybyte(win, idx.y, idx.x, tmap->map[pc]);
		idx.x += 3;
		if (((pc + 1) % CONTENTS_BYTES_PER_LINE) == 0)
		{
			idx.x = CONTENTS_START_X;
			idx.y += 1;
		}
		pc++;
	}
	wrefresh(win);
	colors_off_pc(win, tarena, pc);
}

static void			ncur_make_black(t_windows *twin)
{
	int i;
	int j;

	i = 0;
	wattron(twin->win_arena, COLOR_PAIR(9) | A_BOLD);
	wattron(twin->win_info, COLOR_PAIR(9) | A_BOLD);
	while (i < CONTENTS_TOTAL_LINES)
	{
		j = 0;
		wmove(twin->win_arena, i, 0);
		while (j < CONTENTS_TOTAL_COLS)
		{
			waddch(twin->win_arena, ' ');
			j++;
		}
		i++;
	}
	i = 0;
	while (i < INFO_TOTAL_LINES)
	{
		j = 0;
		wmove(twin->win_arena, i, 0);
		while (j < INFO_TOTAL_COLS)
		{
			waddch(twin->win_info, ' ');
			j++;
		}
		i++;
	}
	wattroff(twin->win_arena, COLOR_PAIR(9) | A_BOLD);
	wattroff(twin->win_info, COLOR_PAIR(9) | A_BOLD);
	wrefresh(twin->win_arena);
	wrefresh(twin->win_info);
}


t_windows		*ncur_new(t_arena *tarena)
{
	t_windows	*twin;

	initscr();
	noecho();
	refresh();
	twin->win_arena = newwin(CONTENTS_TOTAL_LINES,
							CONTENTS_TOTAL_COLS,
							0, 0);
	twin->win_info = newwin(INFO_TOTAL_LINES,
							INFO_TOTAL_COLS,
							0, CONTENTS_TOTAL_COLS - 1);
	colors_init(twin->win_arena);
	colors_init(twin->win_info);
	bkgd(COLOR_PAIR(9));
	refresh();
	wbkgd(twin->win_arena, COLOR_PAIR(9));
	wbkgd(twin->win_info, COLOR_PAIR(9));
	wattroff(twin->win_arena, COLOR_PAIR(9));
	wattroff(twin->win_info, COLOR_PAIR(9));
	wattron(twin->win_arena, COLOR_PAIR(5) | A_BOLD);
	wattron(twin->win_info, COLOR_PAIR(5) | A_BOLD);
	wborder(twin->win_arena, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(twin->win_info, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(twin->win_info, COLOR_PAIR(5) | A_BOLD);
	wattron(twin->win_arena, COLOR_PAIR(7) | A_BOLD);

	ncur_show_termsays(twin->win_arena);
	ncur_map_init(twin->win_arena, tarena->tmap, tarena);
	info_show_status(twin->win_info, 1);
	info_show_cycle(twin->win_info, tarena->cycle);
	info_show_process(twin->win_info, tarena->num_process);
	info_show_cham_init(twin->win_info, tarena);
	info_show_cycle_die_period(twin->win_info, tarena);
	info_show_constants(twin->win_info, tarena);
	wrefresh(twin->win_info);
	wrefresh(twin->win_arena);
	return (twin);
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

