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

void        show_commands_zjmp(t_proc *tproc, int where)
{
    ft_printf("P%5d | ", tproc->number + 1);
    ft_printf("zjmp %d ", where);
    if (tproc->carry)
        ft_printf("OK\n");
    else
        ft_printf("FAILED\n");
}

void        show_commands_st(t_proc *tproc, t_arg *targ, int where)
{
    ft_printf("P%5d | ", tproc->number + 1);
    ft_printf("st r%d ", ((char*)(targ->arg))[0]);
    if (targ->bytecode[1] == T_REG)
        ft_printf("%d\n", ((char*)(targ->arg))[1]);
    else
        ft_printf("%d\n", where);
}

void        show_commands_ld(t_proc *tproc, t_type_arg type_arg)
{
    ft_printf("P%5d | ", tproc->number + 1);
    ft_printf("ld %d r%d\n", type_arg.val_reg[3], type_arg.adr_reg[3]);
}

void        show_commands_lld(t_proc *tproc, t_type_arg type_arg)
{
    ft_printf("P%5d | ", tproc->number + 1);
    ft_printf("lld %d r%d\n", type_arg.val_reg[3], type_arg.adr_reg[3]);
}
