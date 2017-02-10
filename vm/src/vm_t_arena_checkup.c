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

	idx_cham = 0;
	while (idx_cham < tarena->num_cham)
	{
		idx_proc = 0;
		while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
		{
			if (tarena->tcham[idx_cham]->tproc[idx_proc].period_live == 0)
			{
				tarena->num_process -= 1;
				t_champion_kill_proc(tarena->tcham[idx_cham], idx_proc);
				if (tarena->option & NCURSES)
				{
					info_show_process(tarena->twin->win_info, tarena->num_process);
					ncur_unhighlight_pc(tarena->twin->win_arena, tarena->tmap,
						&(tarena->tcham[idx_cham]->tproc[idx_proc]),
						tarena);
				}
			}
			else
			{
				tarena->tcham[idx_cham]->tproc[idx_proc].period_live = 0;
			}
			idx_proc++;
		}
		if (tarena->option & NCURSES)
			info_show_cham_live_current(tarena->twin->win_info, tarena, idx_cham);
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
			sum_live +=
			tarena->
					tcham[idx_cham]->
									tproc[idx_proc].
													period_live;
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
	if (tarena->num_period - tarena->last_reduce >= 10)//9?
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
