/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:01:39 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 16:01:40 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		*get_bytes_arg(int opcode, int *bytecode, int num_arg)
{
	int *bytes_arg;
	int	i;

	bytes_arg = (int*)malloc(sizeof(int) * num_arg);
	i = 0;
	while (i < num_arg)
	{
		if (bytecode[i] == T_DIR && !(op_tab[opcode - 1].as_address))
			bytes_arg[i] = 4;
		else if (bytecode[i] == T_DIR)
			bytes_arg[i] = 2;
		else if (bytecode[i] == T_IND)
			bytes_arg[i] = 2;
		else if (bytecode[i] == T_REG)
			bytes_arg[i] = 1;
		i++;
	}
	return (bytes_arg);
}


static void		ft_displayspaces(size_t j)
{
	char	spaces[128];
	size_t	total;
	int		i;

	i = 0;
	while (i < 128)
		spaces[i++] = ' ';
	total = 128;
	total -= j * 2;
	total -= j / 2;
	write(1, spaces, total);
}

int		and_arg1_reg_dir(t_proc *tproc, t_arg *targ, t_type_arg *type_arg)
{
	if (targ->bytecode[0] == T_REG)			//get : type_arg.val_reg[i]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg))),
			&(type_arg->val_reg[0])))
			return (-1);
		return (1);
	}
	else if (targ->bytecode[0] == T_DIR)	//get : type_arg.val_dir[i]
	{
		ft_memcpy(&(type_arg->val_dir[0]),
					(char*)(targ->arg),
					DIR_SIZE);
		ft_endian_convert(&(type_arg->val_dir[0]), DIR_SIZE);
		return (4);
	}
	return (0);
}

int		and_arg1_ind(t_arg *targ, t_type_arg *type_arg,
						t_map *tmap, int pc_command)
{
	if (targ->bytecode[0] == T_IND)
	{
		ft_memcpy(&(type_arg->adr_ind[0]),
					(char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg->adr_ind[0]), IND_SIZE);
		type_arg->val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg->adr_ind[0] % IDX_MOD);
		return (2);
	}
	return (0);
}

int		and_arg2_reg_dir(t_proc *tproc, t_arg *targ,
						t_type_arg *type_arg, int point)
{
	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[i]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg)) + point),
			&(type_arg->val_reg[1])))
			return (-1);
		return (1);
	}
	else if (targ->bytecode[1] == T_DIR)	//get : type_arg.val_dir[i]
	{
		ft_memcpy(&(type_arg->val_dir[1]),
					(char*)(targ->arg) + point,
					DIR_SIZE);
		ft_endian_convert(&(type_arg->val_dir[1]), DIR_SIZE);
		return (4);
	}
	return (0);
}

int		and_arg2_ind(t_arg *targ, t_type_arg *type_arg,
					t_map *tmap, int pc_command)
{
	if (targ->bytecode[1] == T_IND)
	{
		ft_memcpy(&(type_arg->adr_ind[1]),
					(char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg->adr_ind[1]), IND_SIZE);
		type_arg->val_ind[1] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg->adr_ind[1] % IDX_MOD);
		return (2);
	}
	return (0);
}

int		and_arg123(t_execute_variable *var)
{
	int point[3];

	if (var->targ->bytecode[0] == T_REG ||
		var->targ->bytecode[0] == T_DIR)
		point[0] = and_arg1_reg_dir(var->tproc, var->targ, &(var->type_arg));
	else
		point[0] = and_arg1_ind(var->targ, &(var->type_arg), var->tmap, var->pc_command);
	if (point[0] == -1)
		return (-1);
	if (var->targ->bytecode[1] == T_REG ||
		var->targ->bytecode[1] == T_DIR)
		point[1] = and_arg2_reg_dir(var->tproc, var->targ, &(var->type_arg), point[0]);
	else
		point[1] = and_arg2_ind(var->targ, &(var->type_arg), var->tmap, var->pc_command);
	if (point[1] == -1)
		return (-1);
	point[2] = point[0] + point[1];
	var->type_arg.adr_reg[2] = *(((char*)(var->targ->arg)) + point[2]);
	point[2] += 1;
	return (point[2]);
}


void	draw_repeat_ch_hor(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x, y + i);
		waddch(win, ch);
		i++;
	}
}

void	draw_repeat_ch_ver(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x + i, y);
		waddch(win, ch);
		i++;
	}
}

void			t_arena_showinfo(t_arena *tarena)
{
	int i;

	i = 0;

	ft_putstr("----------------------------------\n");
	ft_putstr("Cycle : ");
	ft_putnbr(tarena->cycle - 1);
	ft_putstr("\n");

	ft_putstr("Period : ");
	ft_putnbr(tarena->num_period);
	ft_putstr("\n");

	printf("num p : %d\n", tarena->num_process);
	ft_putstr("Number of Process : ");
	ft_putnbr(tarena->num_process);
	ft_putstr("\n");

	ft_putstr("Cycle to die : ");
	ft_putnbr(tarena->cycle_to_die);
	ft_putstr("\n");

	ft_putstr("Last alive cham : ");
	ft_putnbr(tarena->tcham[tarena->last_alive_cham]->number);
	ft_putstr("\n");
	ft_putstr("----------------------------------\n");
}

void			t_champion_showinfo(t_champion *tcham)
{
	int i;
	int j;
	int num;

	ft_putstr("Champion Number :\t");
	ft_putnbr(tcham->number);
	ft_putstr("\n");
	
	ft_putstr("Filename :\t\t");
	ft_putstr(tcham->tfile.fname);
	ft_putstr("\n");
	
	ft_putstr("Size :\t\t\t");
	ft_putnbr(tcham->theader.prog_size);
	ft_putstr("\n");
	
	ft_putstr("Name :\t\t\t");
	ft_putstr(tcham->theader.prog_name);
	ft_putstr("\n");
	
	ft_putstr("Comment :\t\t");
	ft_putstr(tcham->theader.comment);
	ft_putstr("\n");
	ft_putstr("\n");

	i = 0;
	while (i < tcham->num_tproc)
	{
		ft_putstr("proc num : ");
		ft_putnbr(i);
		ft_putstr("\n");
		ft_putstr("pc :\t");
		ft_putnbr(tcham->tproc[i].pc);
		ft_putstr("\n");
		ft_putstr("carry :\t");
		ft_putnbr(tcham->tproc[i].carry);
		ft_putstr("\n");
		j = 0;
		while (j < REG_NUMBER)
		{
			ft_memcpy(&num, (tcham->tproc[i]).registry[j], REG_SIZE);
			ft_putstr("[r");
			ft_putnbr(j + 1);
			ft_putstr("] : ");
			ft_putnbr(num);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
		ft_putstr("\n");
		i++;
	}
}

int		t_map_put_one(t_map *tmap, int fd, int start)
{
	char	*str;
	int check;

	if (fd < 0)
		return (-1);
	check = ft_read_all(fd, &str);
	if (check == -1)
		ft_exit_error("Wrong file");
	if (ft_strlen(str) > tmap->size_map)
		ft_exit_error("File length is too long");
	ft_memcpy(tmap->map + start,
				str + LENGTH_BEFORE_INST,
				check - (LENGTH_BEFORE_INST));
	free(str);
	return (0);
}

int 	t_map_put_all(t_map *tmap, int fd[], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		t_map_put_one(tmap, fd[i], ((MEM_SIZE) / size * i));
		i++;
	}
	return (0);
}

int 			t_proc_find_minproc(t_arena *tarena, int min,
									int *idx_cham_store, int *idx_proc_store)
{
	int success;
	int idx_cham;
	int idx_proc;
	int num_proc;

	success = 0;
	while (!success)
	{
		idx_cham = 0;
		while (idx_cham < tarena->num_cham)
		{
			idx_proc = 0;
			while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
			{
				if (tarena->tcham[idx_cham]->tproc[idx_proc].number == min)
				{
					success = 1;
					break ;
				}
				idx_proc++;
			}
			if (success)
				break ;
			idx_cham++;
		}
		min++;
	}
	*idx_cham_store = idx_cham;
	*idx_proc_store = idx_proc;
	return (min);
}


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

static void			ncur_make_black(t_windows *twin)
{
	int i;
	int j;

	i = 0;
	wattron(twin->win_arena, COLOR_PAIR(9) | A_BOLD);
	wattron(twin->win_info, COLOR_PAIR(9) | A_BOLD);
	while (i < CONTENTS_TOTAL_LINES)
	{
		j = 0;
		wmove(twin->win_arena, i, 0);
		while (j < CONTENTS_TOTAL_COLS)
		{
			waddch(twin->win_arena, ' ');
			j++;
		}
		i++;
	}
	i = 0;
	while (i < INFO_TOTAL_LINES)
	{
		j = 0;
		wmove(twin->win_arena, i, 0);
		while (j < INFO_TOTAL_COLS)
		{
			waddch(twin->win_info, ' ');
			j++;
		}
		i++;
	}
	wattroff(twin->win_arena, COLOR_PAIR(9) | A_BOLD);
	wattroff(twin->win_info, COLOR_PAIR(9) | A_BOLD);
	wrefresh(twin->win_arena);
	wrefresh(twin->win_info);
}

// int		w_deal_live(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc)
// {
// 	t_arg	*targ;
// 	int		num;
// 	int		ret;
// 	int		live_cham;

// 	ret = count_bytecode_cycle(tmap, OP_LIVE + 1, tarena->tcham[idx_cham]->tproc[idx_proc].pc)
// 				+ op_tab[OP_LIVE].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, OP_LIVE + 1);
// 	if (targ == NULL)
// 	{
// 		#ifdef __DEBUG_JEX
// 			printf("%s\n", "wrong exit");
// 		#endif
// 		return (ret);//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
// 	}
// 	ft_memcpy(&num, targ->arg, 4);
// 	ft_endian_convert(&num, 4);
// 	num *= -1;
// 	if (num < 0 || num > tarena->num_cham)//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
// 	{
// 		#ifdef __DEBUG_JEX
// 			printf("%s\n", "wrong exit");
// 		#endif
// 		return (ret);
// 	}
// 	tarena->tcham[idx_cham]->tproc[idx_proc].period_live += 1;
// 	if ((live_cham = change_last_live(tarena->tcham, tarena->num_cham,
// 							num, tarena->cycle))
// 		!= -1)
// 	{
// 		tarena->last_alive_cham = live_cham;
// 		tarena->tcham[live_cham]->current_live += 1;
// 		info_show_cham_lastlive(tarena->twin->win_info, tarena, live_cham);
// 		info_show_cham_live_current(tarena->twin->win_info, tarena, live_cham);
// 		ncur_show_live(tarena->twin->win_arena, tarena, idx_cham, live_cham);
// 	}
// 	t_arg_destroy(targ);
// 	return (ret);
// }

