/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_lfork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:54:31 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 00:54:32 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

//이제 이거 쓰면 안댐
// int		deal_lfork(t_map *tmap, t_champion *tcham,
// 					int idx_proc, int pc_command)
// {
// 	t_arg			*targ;
// 	t_type_arg		type_arg;
// 	int				ret;

// 	ret = count_bytecode_cycle(tmap, OP_LFORK + 1, pc_command)
// 				+ op_tab[OP_LFORK].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_LFORK + 1);
// 	if (targ == NULL)
// 	{
// 		#ifdef __DEBUG_JEX
// 			printf("%s\n", "wrong exit");
// 		#endif
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}

// 	ft_memcpy(&(type_arg.adr_dir[0]),
// 				(char*)(targ->arg),
// 				DIR_ADR_SIZE);
// 	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
// 	//type_arg.adr_dir[0] %= IDX_MOD;
// 	// tarena->num_process += 1;
// 	t_champion_add_proc(tcham, idx_proc, 
// 						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE,
// 						tarena->used_proc_num);
// 	tarena->used_proc_num += 1;
// 	t_arg_destroy(targ);
// 	return (ret);
// }

int		w_deal_lfork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;
	int				where;

	ret = count_bytecode_cycle(tarena->tmap, OP_LFORK + 1, pc_command)
				+ op_tab[OP_FORK].num_bytecode
				+ 1;
	targ = t_arg_new(tarena->tmap, pc_command, OP_LFORK + 1);
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	ft_memcpy(&(type_arg.adr_dir[0]),
				(char*)(targ->arg),
				DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	//type_arg.adr_dir[0] %= IDX_MOD;
	where = (pc_command + type_arg.adr_dir[0]) % MEM_SIZE;
	if (where < 0)
		where += MEM_SIZE;
	//debug
		// if (tarena->tcham[idx_cham]->tproc[idx_proc].number + 1 == 64)
		// {
		// 	printf("pc_command  %d\n", pc_command);
		// 	printf("type_arg.adr_dir[0] %d\n", type_arg.adr_dir[0]);
		// 	printf("(pc_command + type_arg.adr_dir[0]) %% MEM_SIZE : %d\n",
		// 			(pc_command + type_arg.adr_dir[0]) % MEM_SIZE);
		// 	printf("where : %d\n", where);
		// }
	//debug
	tarena->num_process += 1;
	t_champion_add_proc(tarena->tcham[idx_cham], idx_proc, 
						where,
						tarena->used_proc_num);
	tarena->used_proc_num += 1;
	if (tarena->option & NCURSES)
		info_show_process(tarena->twin->win_info, tarena->num_process);
	if (tarena->option & COMMANDS)
		show_commands_lfork(&(tarena->tcham[idx_cham]->tproc[idx_proc]), type_arg,
							pc_command + type_arg.adr_dir[0]);
	t_arg_destroy(targ);
	return (ret);
}
