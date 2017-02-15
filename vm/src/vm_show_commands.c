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

void		show_commands_sti(t_arg *targ, t_type_arg type_arg,
								t_proc *tproc, int where)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
	printf("sti r%d ", ((char*)(targ->arg))[0]);
	if (targ->bytecode[2] == T_REG)
	{
		if (targ->bytecode[1] == T_REG)
			num1 = type_arg.val_reg[1];
		else if (targ->bytecode[1] == T_DIR)
			num1 = type_arg.adr_dir[1];
		else
			num1 = type_arg.val_ind[1];
		num2 = type_arg.val_reg[2];
	}
	else //T_DIR
	{
		if (targ->bytecode[1] == T_REG)
			num1 = type_arg.val_reg[1];
		else if (targ->bytecode[1] == T_DIR)
			num1 = type_arg.adr_dir[1];
		else
			num1 = type_arg.val_ind[1];
		num2 = type_arg.adr_dir[2];
	}

	printf("%d %d\n", num1, num2);
	printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			num1, num2, num1 + num2, where);
}

void		show_commands_ldi(t_arg *targ, t_type_arg type_arg,
								t_proc *tproc, int where)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
	printf("ldi ");
	if (targ->bytecode[1] == T_REG)
	{
		if (targ->bytecode[0] == T_REG)
			num1 = type_arg.val_reg[0];
		else if (targ->bytecode[0] == T_DIR)
			num1 = type_arg.adr_dir[0];
		else
			num1 = type_arg.val_ind[0];
		num2 = type_arg.val_reg[1];
	}
	else //(targ->bytecode[1] == T_DIR)
	{
		if (targ->bytecode[0] == T_REG)
			num1 = type_arg.val_reg[0];
		else if (targ->bytecode[0] == T_DIR)
			num1 = type_arg.adr_dir[0];
		else
			num1 = type_arg.val_ind[0];
		num2 = type_arg.adr_dir[1];
	}
	printf("%d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
	printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			num1, num2, num1 + num2, where);
}


void		show_commands_zjmp(t_proc *tproc, int where)
{
	printf("P%5d | ", tproc->number + 1);
	printf("zjmp %d ", where);
	if (tproc->carry)
		printf("OK\n");
	else
		printf("FAILED\n");
}

void		show_commands_st(t_proc *tproc, t_arg *targ, int where)
{
	printf("P%5d | ", tproc->number + 1);
	printf("st r%d ", ((char*)(targ->arg))[0]);
	if (targ->bytecode[1] == T_REG)
		printf("%d\n", ((char*)(targ->arg))[1]);
	else
		printf("%d\n", where);
}

void		show_commands_ld(t_proc *tproc, t_type_arg type_arg)
{
	printf("P%5d | ", tproc->number + 1);
	printf("ld %d r%d\n", type_arg.val_reg[3], type_arg.adr_reg[3]);
}

void		show_commands_fork(t_proc *tproc, t_type_arg type_arg, int where)
{
	printf("P%5d | ", tproc->number + 1);
	printf("fork %d (%d)\n", type_arg.adr_dir[0], where);
}

void		show_commands_lfork(t_proc *tproc, t_type_arg type_arg, int where)
{
	printf("P%5d | ", tproc->number + 1);
	printf("lfork %d (%d)\n", type_arg.adr_dir[0], where);
}

void		show_commands_live(t_proc *tproc, int num)
{
	printf("P%5d | ", tproc->number + 1);
	printf("live %d\n", num);
}

void		show_commands_sub(t_proc *tproc, t_arg *targ)
{
	printf("P%5d | ", tproc->number + 1);
	printf("sub r%d r%d r%d\n", ((char*)(targ->arg))[0], ((char*)(targ->arg))[1], ((char*)(targ->arg))[2]);
}

void		show_commands_add(t_proc *tproc, t_arg *targ)
{
	printf("P%5d | ", tproc->number + 1);
	printf("and r%d r%d r%d\n", ((char*)(targ->arg))[0], ((char*)(targ->arg))[1], ((char*)(targ->arg))[2]);
}

void		show_commands_or(t_proc *tproc, t_arg *targ, t_type_arg type_arg)
{
	int num1;
	int num2;

	printf("P%5d | ", tproc->number + 1);
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
	printf("or %d %d r%d\n", num1, num2, type_arg.adr_reg[2]);
}



