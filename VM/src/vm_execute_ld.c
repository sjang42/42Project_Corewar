/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_ld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:12:55 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:12:57 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int      get_first_arg(t_arg *targ, t_type_arg *type_arg,
                                t_map *tmap, int pc_command)
{
    if (targ->bytecode[0] == T_DIR)
    {
        ft_memcpy(&(type_arg->val_dir[0]),
                    (char*)(targ->arg),
                    DIR_SIZE);
        ft_endian_convert(&(type_arg->val_dir[0]), DIR_SIZE);
        return (4);
    }
    else
    {
        ft_memcpy(&(type_arg->adr_ind[0]), (char*)(targ->arg), IND_SIZE);
        ft_endian_convert(&(type_arg->adr_ind[0]), IND_SIZE);
        type_arg->val_ind[0] = (TYPE_IND)read_indirect_data(
                            tmap, pc_command,
                            type_arg->adr_ind[0] % IDX_MOD);
        return (2);
    }
}

static int      get_second_arg(t_arg *targ, t_type_arg *type_arg, int point)
{
    type_arg->adr_reg[3] = *((char*)targ->arg + point);
    type_arg->val_reg[3] = (targ->bytecode[0] == T_DIR) ?
                            type_arg->val_dir[0] :
                            type_arg->val_ind[0];
    return (1);
}

int             deal_ld(t_arena *tarena, t_map *tmap,
                        int pc_command, t_proc *tproc)
{
    t_arg           *targ;
    t_type_arg      type_arg;
    int             point;
    int             ret;

    if ((targ = get_ret_targ(tarena->tmap, &ret,
                OP_LD + 1, pc_command)) == NULL)
        return (ret);
    point = get_first_arg(targ, &type_arg, tmap, pc_command);
    point += get_second_arg(targ, &type_arg, point);
    if (put_registry(tproc->registry, type_arg.adr_reg[3],
                    &type_arg.val_reg[3]))
    {
        t_arg_destroy(targ);
        return (ret);
    }
    tproc->carry = (type_arg.val_reg[3] == 0) ? 1 : 0;
    if (tarena->option & COMMANDS)
        show_commands_ld(tproc, type_arg);
    t_arg_destroy(targ);
    return (ret);
}
