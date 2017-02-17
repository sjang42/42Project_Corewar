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

static int		decide_number(t_arena *tarena)
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

static void		sort_champions(t_arena *tarena, int idx_cham,
								int count, int max)
{
	int			min[2];
	t_champion	**tcham_sort;

	tcham_sort = (t_champion**)malloc(sizeof(t_champion*) * tarena->num_cham);
	while (count < tarena->num_cham)
	{
		min[0] = 10000;
		idx_cham = 0;
		while (idx_cham < tarena->num_cham)
		{
			if (min[0] > tarena->tcham[idx_cham]->number &&
				max < tarena->tcham[idx_cham]->number)
			{
				min[1] = idx_cham;
				min[0] = tarena->tcham[idx_cham]->number;
			}
			idx_cham++;
		}
		max = tarena->tcham[min[1]]->number;
		tcham_sort[count] = tarena->tcham[min[1]];
		tcham_sort[count]->tproc[0].number = count;
		count++;
	}
	free(tarena->tcham);
	tarena->tcham = tcham_sort;
}

static void		fill_tarena_basic(t_arena *tarena, int argc, char *argv[])
{
	int idx_argv;

	tarena->tmap = t_map_new(MEM_SIZE);
	tarena->num_period = 0;
	tarena->last_reduce = 0;
	tarena->dump = 0;
	tarena->game_done = 0;
	tarena->used_proc_num = 0;
	tarena->last_alive_cham = -1;
	idx_argv = 1;
	while (idx_argv < argc - 1)
	{
		if (!ft_strcmp(argv[idx_argv], "-dump") &&
			ft_isonly_digit(argv[idx_argv + 1]))
		{
			tarena->dump = ft_atoi(argv[idx_argv + 1]);
			break ;
		}
		idx_argv++;
	}
}

static void		fill_tarena_champions(t_arena *tarena, int argc,
										char *argv[], int color)
{
	int		idx_argv;
	int		cham_num;

	idx_argv = ft_get_option(argc, argv, &(tarena->option));
	tarena->tcham = (t_champion**)malloc(sizeof(t_champion*) * (argc - 1));
	tarena->num_cham = 0;
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
		tarena->tcham[tarena->num_cham] = t_champion_new(
						argv[idx_argv], cham_num, color, tarena->used_proc_num);
		tarena->used_proc_num += 1;
		tarena->num_cham += 1;
		color++;
		idx_argv++;
	}
	sort_champions(tarena, 0, 0, -1);
}

t_arena			*t_arena_new(int argc, char *argv[])
{
	t_arena		*tarena;

	tarena = (t_arena*)malloc(sizeof(t_arena));
	fill_tarena_basic(tarena, argc, argv);
	fill_tarena_champions(tarena, argc, argv, 1);
	tarena->num_process = tarena->num_cham;
	t_map_put_chams(tarena->tmap, tarena->tcham, tarena->num_cham);
	tarena->cycle = 1;
	tarena->cycle_to_die = CYCLE_TO_DIE;
	return (tarena);
}
