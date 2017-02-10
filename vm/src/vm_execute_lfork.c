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

int		deal_lfork(t_map *tmap, t_champion *tcham,
					int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ret = count_bytecode_cycle(tmap, OP_LFORK + 1, pc_command)
				+ op_tab[OP_LFORK].num_bytecode
				+ 1;
	targ = t_arg_new(tmap, pc_command, OP_LFORK + 1);
	if (targ == NULL)
		return (ret);//틀렸을 때 몇 개 반환하는지 보기

	ft_memcpy(&(type_arg.adr_dir[0]),
				(char*)(targ->arg),
				DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	//type_arg.adr_dir[0] %= IDX_MOD;
	// tarena->num_process += 1;
	t_champion_add_proc(tcham, idx_proc, 
						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE);
	t_arg_destroy(targ);
	return (ret);
}

int		w_deal_lfork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ret = count_bytecode_cycle(tarena->tmap, OP_LFORK + 1, pc_command)
				+ op_tab[OP_FORK].num_bytecode
				+ 1;
	targ = t_arg_new(tarena->tmap, pc_command, OP_LFORK + 1);
	if (targ == NULL)
		return (ret);//틀렸을 때 몇 개 반환하는지 보기

	ft_memcpy(&(type_arg.adr_dir[0]),
				(char*)(targ->arg),
				DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	//type_arg.adr_dir[0] %= IDX_MOD;
	tarena->num_process += 1;
	t_champion_add_proc(tarena->tcham[idx_cham], idx_proc, 
						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE);
	//ncurses
	info_show_process(tarena->twin->win_info, tarena->num_process);
	//
	t_arg_destroy(targ);
	return (ret);
}
