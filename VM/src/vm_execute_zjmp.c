/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:06:25 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 21:06:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int     deal_zjmp(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc)
{
    t_arg           *targ;
    t_type_arg      type_arg;
    int             ret;
    int             where;

    if ((targ = get_ret_targ(tmap, &ret, OP_ZJMP + 1, pc_command)) == NULL)
        return (ret);
    ft_memcpy(&(type_arg.adr_dir[0]), (char*)(targ->arg),
                DIR_ADR_SIZE);
    ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
    if (tproc->carry)
    {
        where = (tproc->pc + (type_arg.adr_dir[0] % (IDX_MOD))) % MEM_SIZE;
        if (where < 0)
            where += MEM_SIZE;
        tproc->pc = where;
        ret = 0;
    }
    if (tarena->option & COMMANDS)
        show_commands_zjmp(tproc, type_arg.adr_dir[0]);
    t_arg_destroy(targ);
    return (ret);
}
