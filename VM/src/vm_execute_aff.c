/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 22:11:21 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 22:11:22 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static void     show_aff(t_arena *tarena, int idx_cham, t_type_arg type_arg)
{
    if (tarena->option & NCURSES)
    {
        ncur_show_aff(tarena->twin->win_arena, idx_cham,
                        (char)type_arg.val_reg[0]);
    }
    else
    {
        ft_putstr("Aff : ");
        ft_putchar(type_arg.val_reg[0]);
        ft_putstr("\n");
    }
}

int             deal_aff(t_arena *tarena, int idx_cham, int idx_proc)
{
    t_arg           *targ;
    t_type_arg      type_arg;
    int             ret;
    int             pc_command;

    pc_command = tarena->tcham[idx_cham]->tproc[idx_proc]->pc;
    if ((targ = get_ret_targ(tarena->tmap, &ret,
                OP_AFF + 1, pc_command)) == NULL)
        return (ret);
    if (read_registry(tarena->tcham[idx_cham]->tproc[idx_proc]->registry,
        ((char*)(targ->arg))[0],
        &(type_arg.val_reg[0])))
    {
        t_arg_destroy(targ);
        return (ret);
    }
    show_aff(tarena, idx_cham, type_arg);
    t_arg_destroy(targ);
    return (ret);
}
