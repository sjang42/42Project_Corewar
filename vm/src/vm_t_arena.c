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

int			decide_number(t_arena *tarena)
{
	int i;
	int min;
	int success;

	success = 0;
	min = 1;
	while (!success)
	{
		i = 0;
		while (i < tarena->num_cham)
		{
			if (min == tarena->tcham[i]->number)
				break ;
			i++;
		}
		if (i == tarena->num_cham)
		{
			success = 1;
			break ;
		}
		min++;
	}
	return (min);
}

t_arena 	*t_arena_new(int argc, char *argv[])
{
	t_arena		*tarena;
	int			i;
	int 		idx_argv;
	int 		cham_num;
	int			color;

	tarena = (t_arena*)malloc(sizeof(t_arena));
	tarena->tmap = t_map_new(MEM_SIZE);
	tarena->num_period = 0;
	tarena->last_reduce = 0;
	tarena->dump = 0;
	tarena->game_done = 0;
	tarena->last_alive_cham = -1;
	i = 1;
	while (i < argc - 1)
	{
		if (!ft_strcmp(argv[i], "-dump") &&
			ft_isonly_digit(argv[i + 1]))
		{
			tarena->dump = ft_atoi(argv[i + 1]);
			break ;
		}
		i++;
	}
	idx_argv = ft_get_option(argc, argv, &(tarena->option));
	tarena->tcham = (t_champion**)malloc(sizeof(t_champion*) * (argc - 1));
	tarena->num_cham = 0;
	color = 1;
	while (idx_argv < argc)
	{
		if (idx_argv + 2 < argc &&
			!ft_strcmp(argv[idx_argv], "-n") &&
			ft_isonly_digit(argv[idx_argv + 1]))
		{
			cham_num = ft_atoi(argv[idx_argv + 1]);
			idx_argv += 2;
		}
		else
			cham_num = decide_number(tarena);
		tarena->tcham[tarena->num_cham] = t_champion_new(argv[idx_argv], cham_num, color);
		tarena->num_cham += 1;
		color++;
		idx_argv++;
	}
	tarena->num_process = tarena->num_cham;
	t_map_put_chams(tarena->tmap, tarena->tcham, tarena->num_cham);
	tarena->cycle = 1;
	tarena->cycle_to_die = CYCLE_TO_DIE;
	return (tarena);
}

void		play_one_period(t_arena *tarena)
{
	int		cycle;
	int		idx_cham;
	int		idx_proc;
	int		key;
	int		num_tproc;

	cycle = 0;
	while (cycle < tarena->cycle_to_die)
	{
		if (tarena->option & DUMP && tarena->cycle > tarena->dump)
			break ;
		idx_cham = tarena->num_cham - 1;
		if (tarena->option & NCURSES)
		{
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
		while (idx_cham >= 0)
		{
			idx_proc = 0;
			num_tproc = tarena->tcham[idx_cham]->num_tproc;
			while (idx_proc < num_tproc)
			{
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
				idx_proc++;
			}
			idx_cham--;
		}
		tarena->cycle += 1;
		cycle++;
	}
	if (tarena->option & NCURSES)
		info_show_cycle(tarena->twin->win_info, tarena->cycle);
}

// void		play_one_period(t_arena *tarena)
// {
// 	int		cycle;
// 	int		idx_cham;
// 	int		idx_proc;

// 	cycle = 0;
// 	while (cycle < tarena->cycle_to_die)
// 	{
// 		idx_cham = tarena->num_cham - 1;
// 		while (idx_cham >= 0)
// 		{
// 			idx_proc = 0;
// 			while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
// 			{
// 				tarena->tcham[idx_cham]->tproc[idx_proc].pc =
// 				(vm_execute_proc(tarena->tmap,
// 								tarena->tcham[idx_cham],
// 								tarena,
// 								idx_proc)
// 				+ tarena->tcham[idx_cham]->tproc[idx_proc].pc)
// 				% MEM_SIZE;
// 				idx_proc++;
// 			}
// 			idx_cham--;
// 		}
// 		tarena->cycle += 1;
// 		cycle++;
// 	}
// }

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
	if (tarena->option & NCURSES)
		info_show_status(tarena->twin->win_info, 0);
	while (1)
	{
		play_one_period(tarena);
		tarena->num_period += 1;
		checkup_nbr_live(tarena);
		checkup_max_checks(tarena);
		checkup_proc(tarena);
		if (tarena->option & NCURSES)
		{
			info_show_cycle_die_period(tarena->twin->win_info, tarena);
			// getch();
		}
		if (count_alive_cham(tarena) <= 0)
		{
			tarena->game_done = 1;
			break;
		}
		else if ((tarena->option & DUMP) &&
			tarena->cycle == (tarena->dump + 1))
			break;
	}
}

void			t_arena_showinfo(t_arena *tarena)
{
	ft_putstr("----------------------------------\n");
	ft_putstr("Cycle :\t");
	ft_putnbr(tarena->cycle - 1);
	ft_putstr("\n");

	ft_putstr("Number of Process :\t");
	ft_putnbr(tarena->num_process);
	ft_putstr("\n");

	ft_putstr("Cycle to die :\t");
	ft_putnbr(tarena->cycle_to_die);
	ft_putstr("\n");

	ft_putstr("Last alive cham :\t");
	ft_putnbr(tarena->last_alive_cham);
	ft_putstr("\n");
	ft_putstr("----------------------------------\n");
}













