/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:14:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 16:14:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int 	*fill_fds(int argc, char *argv[])
{
	int 	*fd;
	int		i;

	fd = (int*)malloc(sizeof(int) * (argc - 1));
	i = 0;
	while (i < argc - 1)
	{
		fd[i] = open(argv[i + 1], O_RDONLY);
		if (fd[i] == -1)
			ft_exit_error("Fail to open file");
		i++;
	}
	return (fd);
}

int		main(int argc, char *argv[])
{
	int 	i;
	int		j;
	int		idx_cham;
	int		*fd;
	t_map	*tmap;
	t_champion **tcham;

	fd = fill_fds(argc, argv);
	tmap = t_map_new(MEM_SIZE);
	tcham = (t_champion**)malloc(sizeof(t_champion*) * argc - 1);
	i = 0;
	while (i < argc - 1)
	{
		tcham[i] = t_champion_new(argv[i + 1], i + 1);
		// t_champion_showinfo(tcham[i]);
		i++;
	}
	t_map_put_chams(tmap, tcham, argc - 1);
	// print_memory(tmap->map, tmap->size_map);
	// printf("%s\n", "\n");
	i = 0;
	while (i < 100)
	{
		idx_cham = 0;
		while (idx_cham < argc - 1)
		{
			j = 0;
			while (j < tcham[idx_cham]->num_tproc)
			{
				tcham[idx_cham]->tproc[j].pc =
					(vm_execute_proc(tmap, tcham[idx_cham], j) +
					tcham[idx_cham]->tproc[j].pc) %
					MEM_SIZE;
				j++;
			}
			idx_cham++;
		}
		i++;
	}
	ft_print_memory(tmap->map, 64);
	i = 0;
	while (i < argc - 1)
	{
		t_champion_showinfo(tcham[i]);
		i++;
	}
}
