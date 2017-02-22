/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena_play.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 21:16:48 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 21:16:49 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arena.h>

static void		do_checkups(t_arena *tarena)
{
	checkup_nbr_live(tarena);
	checkup_max_checks(tarena);
	checkup_proc(tarena);
}

static void		show_cycle(t_arena *tarena, int origin)
{
	if (tarena->option & CYCLE)
		ft_printf("Period is         : %d\n", tarena->num_period);
	if ((tarena->option & CYCLE) && tarena->cycle_to_die != origin)
		ft_printf("Cycle to die is now %d\n", tarena->cycle_to_die);
}

void			t_arena_play(t_arena *tarena)
{
	int origin;

	if (tarena->option & NCURSES)
		info_show_status(tarena->twin->win_info, 0);
	while (1)
	{
		play_one_period(tarena);
		tarena->num_period += 1;
		if ((tarena->option & DUMP) && tarena->cycle == (tarena->dump + 1))
			break ;
		origin = tarena->cycle_to_die;
		do_checkups(tarena);
		show_cycle(tarena, origin);
		
		if (count_alive_cham(tarena) <= 0)
		{
			tarena->game_done = 1;
			break ;
		}
		if (tarena->option & NCURSES)
		{
			info_show_cycle_die_period(tarena->twin->win_info, tarena);
		}
	}
}
