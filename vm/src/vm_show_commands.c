/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 03:56:54 by sjang             #+#    #+#             */
/*   Updated: 2017/02/11 03:56:55 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static void		sti_get_num12(t_arg *targ, t_type_arg type_arg,
							int *num1, int *num2)
{
	if (targ->bytecode[2] == T_REG)
	{
		if (targ->bytecode[1] == T_REG)
			*num1 = type_arg.val_reg[1];
		else if (targ->bytecode[1] == T_DIR)
			*num1 = type_arg.adr_dir[1];
		else
			*num1 = type_arg.val_ind[1];
		*num2 = type_arg.val_reg[2];
	}
	else
	{
		if (targ->bytecode[1] == T_REG)
			*num1 = type_arg.val_reg[1];
		else if (targ->bytecode[1] == T_DIR)
			*num1 = type_arg.adr_dir[1];
		else
			*num1 = type_arg.val_ind[1];
		*num2 = type_arg.adr_dir[2];
	}
}

void			show_commands_sti(t_arg *targ, t_type_arg type_arg,
								t_proc *tproc, int where)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
	printf("sti r%d ", ((char*)(targ->arg))[0]);
	sti_get_num12(targ, type_arg, &num1, &num2);
	printf("%d %d\n", num1, num2);
	printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			num1, num2, num1 + num2, where);
}

static void		ldi_get_num12(t_arg *targ, t_type_arg type_arg,
							int *num1, int *num2)
{
	if (targ->bytecode[1] == T_REG)
	{
		if (targ->bytecode[0] == T_REG)
			*num1 = type_arg.val_reg[0];
		else if (targ->bytecode[0] == T_DIR)
			*num1 = type_arg.adr_dir[0];
		else
			*num1 = type_arg.val_ind[0];
		*num2 = type_arg.val_reg[1];
	}
	else
	{
		if (targ->bytecode[0] == T_REG)
			*num1 = type_arg.val_reg[0];
		else if (targ->bytecode[0] == T_DIR)
			*num1 = type_arg.adr_dir[0];
		else
			*num1 = type_arg.val_ind[0];
		*num2 = type_arg.adr_dir[1];
	}
}

void			show_commands_ldi(t_arg *targ, t_type_arg type_arg,
								t_proc *tproc, int where)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
	printf("ldi ");
	ldi_get_num12(targ, type_arg, &num1, &num2);
	printf("%d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
	printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			num1, num2, num1 + num2, where);
}

void			show_commands_lldi(t_arg *targ, t_type_arg type_arg,
								t_proc *tproc, int where)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
	printf("lldi ");
	ldi_get_num12(targ, type_arg, &num1, &num2);
	printf("%d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
	printf("       | -> load from %d + %d = %d (with pc %d)\n",
			num1, num2, num1 + num2, where);
}
