/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:03:57 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:03:58 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_add(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;	

	targ = t_arg_new(tmap, pc_command, OP_ADD + 1);
	if (targ == NULL)
		return (5);//틀렸을 때 몇 개 반환하는지 보기
	if (read_registry(tproc->registry,
						((char*)(targ->arg))[0],
						&(type_arg.val_reg[0]))
		||
		read_registry(tproc->registry,
						((char*)(targ->arg))[1],
						&(type_arg.val_reg[1]))
		||
		read_registry(tproc->registry,
						((char*)(targ->arg))[2],
						&(type_arg.val_reg[2]))
		)
	{
		t_arg_destroy(targ);
		return (5);//틀렸을 때 몇 개 반환하는지 보기
	}
	type_arg.val_reg[3] = type_arg.val_reg[0] + type_arg.val_reg[1];
	put_registry(tproc->registry, ((char*)(targ->arg))[2], &(type_arg.val_reg[3]));

	if (type_arg.val_reg[3] == 0)
		tproc->carry = 1;
	t_arg_destroy(targ);
	return (5);
}
