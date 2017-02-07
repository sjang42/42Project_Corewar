/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 19:04:13 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 19:04:15 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arena.h>

t_arena 	*t_arena_new(int argc, char *argv[], int number[])
{
	t_arena		*tarena;
	int			i;

	tarena = (t_arena*)malloc(sizeof(t_arena));
	tarena->tmap = t_map_new(MEM_SIZE);
	tarena->num_cham = argc - 1;
	tarena->num_period = 0;
	tarena->last_reduce = 0;
	tarena->last_alive_cham = -1;
	tarena->tcham = (t_champion**)malloc(sizeof(t_champion*) * (tarena->num_cham));
	i = 0;
	while (i < argc - 1)
	{
		tarena->tcham[i] = t_champion_new(argv[i + 1], number[i]);
		i++;
	}
	t_map_put_chams(tarena->tmap, tarena->tcham, tarena->num_cham);
	tarena->cycle = 0;
	tarena->cycle_to_die = CYCLE_TO_DIE;
	return (tarena);
}

void		play_one_period(t_arena *tarena)
{
	int		cycle;
	int		idx_cham;
	int		idx_proc;

	cycle = 0;
	while (cycle < tarena->cycle_to_die)
	{
		idx_cham = tarena->num_cham - 1;
		while (idx_cham >= 0)
		{
			idx_proc = 0;
			while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
			{
				// ft_putstr("idx_cham : ");
				// ft_putnbr(idx_cham);
				// ft_putstr("\n");
				// printf("cham[%d]->proc[%d]->pc : %d\n",idx_cham ,idx_proc, 	tarena->tcham[idx_cham]->tproc[idx_proc].pc);
				tarena->tcham[idx_cham]->tproc[idx_proc].pc =
				(vm_execute_proc(tarena->tmap,
								tarena->tcham[idx_cham],
								tarena,
								idx_proc)
				+ tarena->tcham[idx_cham]->tproc[idx_proc].pc)
				% MEM_SIZE;
				idx_proc++;
			}
			idx_cham--;
		}
		tarena->cycle += 1;
		cycle++;
	}
}

void		display_winner(t_arena *tarena)
{
	int idx_cham;
	int idx_winner;
	long long	most_last_live;

	idx_cham = 0;
	idx_winner = 0;
	most_last_live = 0;
	while (idx_cham < tarena->num_cham)
	{
		if (tarena->tcham[idx_cham]->last_live >= most_last_live)
		{
			idx_winner = idx_cham;
			most_last_live = tarena->tcham[idx_cham]->last_live;
		}
		idx_cham++;
	}
	ft_putstr("“Player ");
	ft_putnbr(tarena->tcham[idx_winner]->number);
	ft_putstr(" (");
	ft_putstr(tarena->tcham[idx_winner]->theader.prog_name);
	ft_putstr(") won”\n");
}

void		t_arena_play(t_arena *tarena)
{
	while (1)
	{
		play_one_period(tarena);
		tarena->num_period += 1;
		checkup_nbr_live(tarena);
		checkup_max_checks(tarena);
		checkup_proc(tarena);
		if (count_alive_cham(tarena) <= 0)
			break ;
	}
	display_winner(tarena);
}
