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

void			ncur_finish(t_windows *twin)
{
	delwin(twin->win_arena);
	delwin(twin->win_info);
	refresh();
	endwin();
}

void			t_arena_destroy(t_arena *tarena)
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

static void		xy_init(t_xy *xy)
{
	xy->x = CONTENTS_START_X;
	xy->y += 1;
	if (MEM_SIZE / CONTENTS_BYTES_PER_LINE + CONTENTS_START_Y == xy->y)
		xy->y = (CONTENTS_START_Y);
}

void			ncur_map_update(t_arena *tarena, int pc, int size)
{
	int		i;
	t_xy	xy;

	if (pc < 0)
		pc += MEM_SIZE;
	xy.x = (CONTENTS_START_X) + (((pc % (CONTENTS_BYTES_PER_LINE)) * 3));
	xy.y = (CONTENTS_START_Y) + (pc / (CONTENTS_BYTES_PER_LINE));
	if (MEM_SIZE / CONTENTS_BYTES_PER_LINE + CONTENTS_START_Y <= xy.y)
				xy.y = (CONTENTS_START_Y);
	i = 0;
	while (i < size)
	{
		colors_set_pc(tarena->twin->win_arena, tarena, pc);
		w_ft_displaybyte(tarena->twin->win_arena, xy.y, xy.x, tarena->tmap->map[pc]);
		xy.x += 3;
		if (((pc + 1) % CONTENTS_BYTES_PER_LINE) == 0)
			xy_init(&xy);
		colors_off_pc(tarena->twin->win_arena, tarena, pc);
		pc++;
		i++;
	}
	wrefresh(tarena->twin->win_arena);
}
