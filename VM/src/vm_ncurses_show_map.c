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

static void     set_basic(t_windows *twin)
{
    initscr();
    noecho();
    refresh();
    twin->win_arena =
        newwin(CONTENTS_TOTAL_LINES, CONTENTS_TOTAL_COLS, 0, 0);
    twin->win_info =
        newwin(INFO_TOTAL_LINES, INFO_TOTAL_COLS, 0, CONTENTS_TOTAL_COLS - 1);
    colors_init(twin->win_arena);
    colors_init(twin->win_info);
    bkgd(COLOR_PAIR(9));
    refresh();
    wbkgd(twin->win_arena, COLOR_PAIR(9));
    wbkgd(twin->win_info, COLOR_PAIR(9));
    wattroff(twin->win_arena, COLOR_PAIR(9));
    wattroff(twin->win_info, COLOR_PAIR(9));
}

static void     ncur_map_init(WINDOW *win, t_map *tmap, t_arena *tarena)
{
    int             pc;
    t_xy            idx;

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

static void     set_boder(t_windows *twin)
{
    wattron(twin->win_arena, COLOR_PAIR(5) | A_BOLD);
    wattron(twin->win_info, COLOR_PAIR(5) | A_BOLD);
    wborder(twin->win_arena, '*', '*', '*', '*', '*', '*', '*', '*');
    wborder(twin->win_info, '*', '*', '*', '*', '*', '*', '*', '*');
    wattroff(twin->win_info, COLOR_PAIR(5) | A_BOLD);
    wattron(twin->win_arena, COLOR_PAIR(7) | A_BOLD);
}

static void     set_info(t_windows *twin, t_arena *tarena)
{
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
}

t_windows       *ncur_new(t_arena *tarena)
{
    t_windows   *twin;

    twin = (t_windows*)malloc(sizeof(t_windows));
    set_basic(twin);
    set_boder(twin);
    set_info(twin, tarena);
    return (twin);
}
