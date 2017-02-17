/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_commands_part3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:10:53 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 18:10:55 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void		show_commands_fork(t_proc *tproc, t_type_arg type_arg, int where)
{
	ft_printf("P%5d | ", tproc->number + 1);
	ft_printf("fork %d (%d)\n", type_arg.adr_dir[0], where);
}

void		show_commands_lfork(t_proc *tproc, t_type_arg type_arg, int where)
{
	ft_printf("P%5d | ", tproc->number + 1);
	ft_printf("lfork %d (%d)\n", type_arg.adr_dir[0], where);
}

void		show_commands_and(t_proc *tproc, t_arg *targ, t_type_arg type_arg)
{
	int num1;
	int num2;

	ft_printf("P%5d | ", tproc->number + 1);
	if (targ->bytecode[0] == T_REG)
		num1 = type_arg.val_reg[0];
	else if (targ->bytecode[0] == T_DIR)
		num1 = type_arg.val_dir[0];
	else
		num1 = type_arg.val_ind[0];
	if (targ->bytecode[1] == T_REG)
		num2 = type_arg.val_reg[1];
	else if (targ->bytecode[1] == T_DIR)
		num2 = type_arg.val_dir[1];
	else
		num2 = type_arg.val_ind[1];
	ft_printf("and %d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
}

void		show_commands_or(t_proc *tproc, t_arg *targ, t_type_arg type_arg)
{
	int num1;
	int num2;

	ft_printf("P%5d | ", tproc->number + 1);
	if (targ->bytecode[0] == T_REG)
		num1 = type_arg.val_reg[0];
	else if (targ->bytecode[0] == T_DIR)
		num1 = type_arg.val_dir[0];
	else
		num1 = type_arg.val_ind[0];
	if (targ->bytecode[1] == T_REG)
		num2 = type_arg.val_reg[1];
	else if (targ->bytecode[1] == T_DIR)
		num2 = type_arg.val_dir[1];
	else
		num2 = type_arg.val_ind[1];
	ft_printf("or %d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
}

void		show_commands_xor(t_proc *tproc, t_arg *targ, t_type_arg type_arg)
{
	int num1;
	int num2;

	ft_printf("P%5d | ", tproc->number + 1);
	if (targ->bytecode[0] == T_REG)
		num1 = type_arg.val_reg[0];
	else if (targ->bytecode[0] == T_DIR)
		num1 = type_arg.val_dir[0];
	else
		num1 = type_arg.val_ind[0];
	if (targ->bytecode[1] == T_REG)
		num2 = type_arg.val_reg[1];
	else if (targ->bytecode[1] == T_DIR)
		num2 = type_arg.val_dir[1];
	else
		num2 = type_arg.val_ind[1];
	ft_printf("xor %d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
}
