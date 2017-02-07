/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:06:25 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 21:06:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_zjmp(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;
	
	ret = count_bytecode_cycle(tmap, OP_ZJMP + 1, pc_command)
				+ op_tab[OP_ZJMP].num_bytecode
				+ 1;
	targ = t_arg_new(tmap, pc_command, OP_ZJMP + 1);
	ft_bzero(&type_arg, sizeof(t_type_arg));
	if (targ == NULL)
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	ft_memcpy(&(type_arg.adr_dir[0]),
				(char*)(targ->arg),
				DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	if (tproc->carry)
	{
		tproc->pc = (tproc->pc + type_arg.adr_dir[0] % IDX_MOD) % MEM_SIZE;
		ret = 0;
	}
	t_arg_destroy(targ);
	return (ret);
}
