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
	int 		i;
	int			num[argc - 1];
	t_arena		*tarena;
	t_windows	*twin;

	tarena = t_arena_new(argc, argv);
	if (tarena->option & NCURSES)
	{
		tarena->twin = ncur_new(tarena);
		wrefresh(tarena->twin->win_arena);
		curs_set(0);
		getch();
	}
	t_arena_play(tarena);
	if (tarena->game_done)
	{
		if (tarena->option & NCURSES)
			ncur_show_winner(tarena->twin->win_arena, tarena);
		else
			display_winner(tarena);
	}
	else if (tarena->option & DUMP)
	{
		t_map_dump(tarena->tmap);
	}
	#ifdef __DEBUG_JEX
		t_arena_showinfo(tarena);
	#endif
	if (tarena->option & NCURSES)
	{
		nocbreak();
		getch();
		curs_set(1);
		ncur_finish(tarena->twin);
	}
	t_arena_destroy(tarena);
}

// int		main(int argc, char *argv[])
// {
// 	int 		i;
// 	int			num[argc - 1];
// 	t_arena		*tarena;

// 	i = 0;
// 	while (i < argc - 1)
// 	{
// 		num[i] = i;
// 		i++;
// 	}
// 	tarena = t_arena_new(argc, argv, num);
// 	t_arena_play(tarena);
// 	play_one_period(tarena);
// 	// ft_print_memory(tarena->tmap->map, 64);
	// i = 0;
	// while (i < argc - 1)
	// {
	// 	t_champion_showinfo(tarena->tcham[i]);
	// 	i++;
	// }
// }