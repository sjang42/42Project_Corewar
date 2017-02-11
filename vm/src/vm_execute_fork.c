/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:06:39 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 21:06:40 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

//이제 이거 쓰면 안댐.
// int		deal_fork(t_map *tmap, t_champion *tcham,
// 					int idx_proc, int pc_command)
// {
// 	t_arg			*targ;
// 	t_type_arg		type_arg;
// 	int				ret;

// 	ret = count_bytecode_cycle(tmap, OP_FORK + 1, pc_command)
// 				+ op_tab[OP_FORK].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_FORK + 1);
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
// 	// tarena->num_process += 1;
// 	type_arg.adr_dir[0] %= IDX_MOD;
// 	t_champion_add_proc(tcham, idx_proc, 
// 						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE,
// 						tarena->used_proc_num);
// 	tarena->used_proc_num += 1;
// 	t_arg_destroy(targ);
// 	return (ret);
// }

int		w_deal_fork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ret = count_bytecode_cycle(tarena->tmap, OP_FORK + 1, pc_command)
				+ op_tab[OP_FORK].num_bytecode
				+ 1;
	targ = t_arg_new(tarena->tmap, pc_command, OP_FORK + 1);
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
	type_arg.adr_dir[0] %= IDX_MOD;
	if (type_arg.adr_dir[0] < 0)
		type_arg.adr_dir[0] += MEM_SIZE;
	tarena->num_process += 1;
	//debug
	//debug
	t_champion_add_proc(tarena->tcham[idx_cham], idx_proc, 
						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE,
						tarena->used_proc_num);
	tarena->used_proc_num += 1;
	//debug
	//debug
	if (tarena->option & NCURSES)
		info_show_process(tarena->twin->win_info, tarena->num_process);
	t_arg_destroy(targ);
	return (ret);
}

