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
	int				ret;

	ret = count_bytecode_cycle(tmap, OP_ADD + 1, pc_command)
				+ op_tab[OP_ADD].num_bytecode
				+ 1;
	targ = t_arg_new(tmap, pc_command, OP_ADD + 1);
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
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
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	type_arg.val_reg[3] = type_arg.val_reg[0] + type_arg.val_reg[1];
	;
	if (put_registry(tproc->registry,
					((char*)(targ->arg))[2],
					&(type_arg.val_reg[3])))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);
	}
	if (type_arg.val_reg[3] == 0)
		tproc->carry = 1;
	else
		tproc->carry = 0;

	t_arg_destroy(targ);
	return (ret);
}
