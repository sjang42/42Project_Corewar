/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena_play_period.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 23:31:27 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 23:31:29 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arena.h>

static void		op_cycle_show(t_arena *tarena)
{
	if (!(tarena->option & CYCLE))
		return ;
	printf("It is now cycle %lld\n", tarena->cycle);
}

static void		op_ncurses_status(t_arena *tarena, int cycle)
{
	int		key;

	if (!(tarena->option & NCURSES))
		return ;
	info_show_cycle(tarena->twin->win_info, tarena->cycle);
	if (cycle % 20 == 0)
	{
		halfdelay(1);
		key = getch();
		if (key == ' ')
		{
			info_show_status(tarena->twin->win_info, 1);
			while (1)
			{
				key = getch();
				if (key == ' ')
					break ;
			}
			info_show_status(tarena->twin->win_info, 0);
		}
	}
}

static void		play_one_cycle(t_arena *tarena, int proc_num, int total_tproc)
{
	int		max;
	int		idx_cham;
	int		idx_proc;

	proc_num = 0;
	max = tarena->used_proc_num;
	total_tproc = tarena->num_process;
	while (proc_num < total_tproc)
	{
		max = t_proc_find_maxproc(tarena, max, &idx_cham, &idx_proc);
		if (tarena->option & NCURSES)
			ncur_unhighlight_pc(tarena->twin->win_arena, tarena->tmap,
				&(tarena->tcham[idx_cham]->tproc[idx_proc]), tarena);
		tarena->tcham[idx_cham]->tproc[idx_proc].pc =
		(vm_execute_proc(tarena->tmap,
			idx_cham,
			tarena,
			idx_proc)
		+ tarena->tcham[idx_cham]->tproc[idx_proc].pc)
		% MEM_SIZE;
		if (tarena->option & NCURSES)
			ncur_highlight_pc(tarena->twin->win_arena, tarena->tmap,
			&(tarena->tcham[idx_cham]->tproc[idx_proc]), tarena);
		proc_num++;
	}
}

void			play_one_period(t_arena *tarena)
{
	int		cycle;

	cycle = 0;
	while (cycle < tarena->cycle_to_die)
	{
		if (tarena->option & DUMP && tarena->cycle > tarena->dump)
			break ;
		op_cycle_show(tarena);
		op_ncurses_status(tarena, cycle);
		delete_just_born(tarena);
		play_one_cycle(tarena, 0, 0);
		tarena->cycle += 1;
		cycle++;
	}
	if (tarena->option & NCURSES)
		info_show_cycle(tarena->twin->win_info, tarena->cycle);
}
