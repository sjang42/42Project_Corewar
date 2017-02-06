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

int		deal_fork(t_map *tmap, t_champion *tcham,
					int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;

	targ = t_arg_new(tmap, pc_command, OP_FORK + 1);
	if (targ == NULL)
		return (5);//틀렸을 때 몇 개 반환하는지 보기

	ft_memcpy(&(type_arg.adr_dir[0]),
				(char*)(targ->arg),
				DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	type_arg.adr_dir[0] %= IDX_MOD;
	t_champion_add_proc(tcham, idx_proc, 
						(pc_command + type_arg.adr_dir[0]) % MEM_SIZE);
	t_arg_destroy(targ);
	return (3);
}
