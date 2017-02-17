/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:16:57 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 00:16:58 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static void		op_ncurses_init(t_arena *tarena)
{
	if (!(tarena->option & NCURSES))
		return ;
	tarena->twin = ncur_new(tarena);
	wrefresh(tarena->twin->win_arena);
	curs_set(0);
	// getch(); why it makes bus error?
}

static void		op_ncurses_end(t_arena *tarena)
{
	if (!(tarena->option & NCURSES))
		return ;
	nocbreak();
	getch();
	curs_set(1);
	ncur_finish(tarena->twin);
}

static void		show_winner(t_arena *tarena)
{
	if (!(tarena->game_done))
		return ;
	if (tarena->option & NCURSES)
		ncur_show_winner(tarena->twin->win_arena, tarena);
	else
		display_winner(tarena);
}

static void		op_dump_dump(t_arena *tarena)
{
	if (tarena->game_done || !(tarena->option & DUMP))
		return ;
	t_map_dump(tarena->tmap);
}

void			corewar(int argc, char *argv[])
{
	t_arena		*tarena;

	tarena = t_arena_new(argc, argv);
	op_ncurses_init(tarena);
	t_arena_play(tarena);
	show_winner(tarena);
	op_dump_dump(tarena);
	op_ncurses_end(tarena);
	t_arena_destroy(tarena);
}
