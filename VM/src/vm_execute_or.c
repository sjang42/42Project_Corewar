/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:39:32 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:39:33 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int      get_first_second_arg(t_execute_variable *var, int i)
{
    if (var->targ->bytecode[i] == T_REG)
    {
        if (read_registry(var->tproc->registry,
            *(((char*)(var->targ->arg) + var->point)),
            &(var->type_arg.val_reg[i])))
            return (-1);
        var->point += 1;
    }
    else if (var->targ->bytecode[i] == T_DIR)
    {
        ft_memcpy(&(var->type_arg.val_dir[i]),
        (char*)(var->targ->arg) + var->point, DIR_SIZE);
        ft_endian_convert(&(var->type_arg.val_dir[i]), DIR_SIZE);
        var->point += 4;
    }
    else
    {
        ft_memcpy(&(var->type_arg.adr_ind[i]),
                    (char*)(var->targ->arg) + var->point, IND_SIZE);
        ft_endian_convert(&(var->type_arg.adr_ind[i]), IND_SIZE);
        var->type_arg.val_ind[i] = (TYPE_IND)read_indirect_data(
            var->tmap, var->pc_command, var->type_arg.adr_ind[i] % IDX_MOD);
        var->point += 2;
    }
    return (0);
}

static int      get_third_arg(t_execute_variable *var)
{
    var->type_arg.adr_reg[2] = *(((char*)(var->targ->arg)) + var->point);
    var->point += 1;
    return (0);
}

static int      or_process(t_arg *targ, t_type_arg *type_arg)
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
    return (num1 | num2);
}

static void     fill_var(t_execute_variable *var, int pc_command,
                            t_proc *tproc, t_map *tmap)
{
    var->pc_command = pc_command;
    var->tproc = tproc;
    var->tmap = tmap;
    var->point = 0;
}

int             deal_or(t_arena *tarena, t_map *tmap,
                        int pc_command, t_proc *tproc)
{
    t_execute_variable  var;
    int                 ret;

    if ((var.targ = get_ret_targ(tmap, &ret, OP_OR + 1, pc_command)) == NULL)
        return (ret);
    fill_var(&var, pc_command, tproc, tmap);
    if (get_first_second_arg(&var, 0) == -1 ||
        get_first_second_arg(&var, 1) == -1)
    {
        t_arg_destroy(var.targ);
        return (ret);
    }
    get_third_arg(&var);
    var.type_arg.val_reg[3] = or_process(var.targ, &(var.type_arg));
    if (put_registry(var.tproc->registry, var.type_arg.adr_reg[2],
                &(var.type_arg.val_reg[3])))
    {
        t_arg_destroy(var.targ);
        return (ret);
    }
    tproc->carry = (var.type_arg.val_reg[3] == 0) ? 1 : 0;
    if (tarena->option & COMMANDS)
        show_commands_or(var.tproc, var.targ, var.type_arg);
    t_arg_destroy(var.targ);
    return (ret);
}
