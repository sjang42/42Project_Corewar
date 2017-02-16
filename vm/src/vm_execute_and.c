/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:39:25 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:39:26 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>


int		and_process(t_arg *targ, t_type_arg *type_arg)
{
	int num1;
	int num2;

	if (targ->bytecode[0] == T_REG)
		num1 = type_arg->val_reg[0];
	else if (targ->bytecode[0] == T_DIR)
		num1 = type_arg->val_dir[0];
	else
		num1 = type_arg->val_ind[0];
	if (targ->bytecode[1] == T_REG)
		num2 = type_arg->val_reg[1];
	else if (targ->bytecode[1] == T_DIR)
		num2 = type_arg->val_dir[1];
	else
		num2 = type_arg->val_ind[1];
	return (num1 & num2);
}

int		deal_and(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_execute_variable	var;
	int					ret;

	if ((var.targ = get_ret_targ(tmap, &ret, OP_AND + 1, pc_command)) == NULL)
		return (ret);
	var.pc_command = pc_command;
	var.tproc = tproc;
	var.tmap = tmap;
	if (and_arg123(&var) == -1)
	{
		t_arg_destroy(var.targ);
		return (ret);
	}
	var.type_arg->val_reg[3] = and_process(var.targ, var.type_arg);
	if (put_registry(var.tproc->registry, var.type_arg->adr_reg[2],
				&(var.type_arg->val_reg[3])))
	{
		t_arg_destroy(var.targ);
		return (ret);
	}
	tproc->carry = (var.type_arg->val_reg[3] == 0) ? 1 : 0;
	t_arg_destroy(var.targ);
	return (ret);
}
