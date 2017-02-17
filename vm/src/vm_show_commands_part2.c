/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_commands_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:10:48 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 18:10:49 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

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

void		show_commands_lld(t_proc *tproc, t_type_arg type_arg)
{
	printf("P%5d | ", tproc->number + 1);
	printf("lld %d r%d\n", type_arg.val_reg[3], type_arg.adr_reg[3]);
}
