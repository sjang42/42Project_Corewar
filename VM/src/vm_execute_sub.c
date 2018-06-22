/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:10:42 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:10:43 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int     deal_sub(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc)
{
    t_arg           *targ;
    t_type_arg      type_arg;
    int             ret;

    if ((targ = get_ret_targ(tmap, &ret, OP_SUB + 1, pc_command)) == NULL)
        return (ret);
    if (read_rgies(tproc, targ, &type_arg) == -1)
    {
        t_arg_destroy(targ);
        return (ret);
    }
    type_arg.val_reg[3] = type_arg.val_reg[0] - type_arg.val_reg[1];
    if (put_registry(tproc->registry, ((char*)(targ->arg))[2],
                    &(type_arg.val_reg[3])))
    {
        t_arg_destroy(targ);
        return (ret);
    }
    tproc->carry = (type_arg.val_reg[3] == 0) ? 1 : 0;
    if (tarena->option & COMMANDS)
        show_commands_sub(tproc, targ);
    t_arg_destroy(targ);
    return (ret);
}
