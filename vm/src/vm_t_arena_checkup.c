/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena_checkup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:23:46 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 22:23:47 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arena.h>

void		checkup_proc(t_arena *tarena)
{
	int idx_cham;
	int idx_proc;
	int num_tproc;
	int i;

	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		i = 0;
		idx_proc = 0;
		num_tproc = tarena->tcham[idx_cham]->num_tproc;
		while (i < num_tproc)
		{
			if (tarena->tcham[idx_cham]->tproc[idx_proc].period_live == 0 &&
				tarena->tcham[idx_cham]->tproc[idx_proc].period_born != 1)
			{
				tarena->num_process -= 1;
				#ifdef __DEBUG_JEX
					printf("one proc killed at cycle : %d\n", tarena->cycle);
				#endif
				if (tarena->option & NCURSES)
				{
					info_show_process(tarena->twin->win_info, tarena->num_process);
					ncur_unhighlight_pc(tarena->twin->win_arena, tarena->tmap,
						&(tarena->tcham[idx_cham]->tproc[idx_proc]),
						tarena);
				}
				t_champion_kill_proc(tarena->tcham[idx_cham], idx_proc);
			}
			else
			{
				tarena->tcham[idx_cham]->tproc[idx_proc].period_live = 0;
				tarena->tcham[idx_cham]->tproc[idx_proc].period_born = 0;
				idx_proc++;
			}
			i++;
		}
		if (tarena->option & NCURSES)
			info_show_cham_live_current(tarena->twin->win_info, tarena, idx_cham);
		tarena->tcham[idx_cham]->current_live = 0;
		idx_cham++;
	}
}

void		checkup_nbr_live(t_arena *tarena)
{
	int idx_cham;
	int idx_proc;
	int sum_live;

	sum_live = 0;
	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		idx_proc = 0;
		while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
		{
			sum_live += tarena->tcham[idx_cham]->
						tproc[idx_proc].period_live;
			idx_proc++;
		}
		idx_cham++;
	}
	if (sum_live >= NBR_LIVE)
	{
		tarena->cycle_to_die -= CYCLE_DELTA;
		tarena->last_reduce = tarena->num_period;
	}
}

void		checkup_max_checks(t_arena *tarena)
{
	if (tarena->num_period - tarena->last_reduce >= MAX_CHECKS)
	{
		tarena->cycle_to_die -= CYCLE_DELTA;
		tarena->last_reduce = tarena->num_period;
	}
}

int			count_alive_cham(t_arena *tarena)
{
	int count;
	int idx_cham;

	count = 0;
	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		if (tarena->tcham[idx_cham]->num_tproc > 0)
			count++;
		idx_cham++;
	}
	return (count);
}

void		delete_just_born(t_arena *tarena)
{
	int idx_cham;
	int idx_proc;

	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		idx_proc = 0;
		while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
		{
			if (tarena->tcham[idx_cham]->tproc[idx_proc].just_born)
				tarena->tcham[idx_cham]->tproc[idx_proc].just_born = 0;
			idx_proc++;
		}
		idx_cham++;
	}
}

void		delete_period_born(t_arena *tarena)
{
	int idx_cham;
	int idx_proc;

	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		idx_proc = 0;
		while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
		{
			if (tarena->tcham[idx_cham]->tproc[idx_proc].period_born)
				tarena->tcham[idx_cham]->tproc[idx_proc].period_born = 0;
			idx_proc++;
		}
		idx_cham++;
	}
}
