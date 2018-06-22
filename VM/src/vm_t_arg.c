/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:25:04 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 16:25:06 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arg.h>
#include <stdio.h>

int         *get_bytecodes(t_map *tmap, int pc_command, int opcode)
{
    int     *bytecode;
    int     i;

    if (op_tab[opcode - 1].num_bytecode == 0)
    {
        bytecode = (int*)malloc(sizeof(int) * op_tab[opcode - 1].num_arg);
        i = 0;
        while (i < op_tab[opcode - 1].num_arg)
        {
            bytecode[i] = op_tab[opcode - 1].argument[i];
            i++;
        }
    }
    else
        bytecode = read_bytecode(
                    tmap, pc_command,
                    op_tab[opcode - 1].num_arg);
    return (bytecode);
}

t_arg       *t_arg_new(t_map *tmap, int pc_command, int opcode)
{
    t_arg       *targ;

    if (opcode < 1 || opcode > 16)
        return (NULL);
    targ = (t_arg*)malloc(sizeof(t_arg));
    ft_bzero(targ, sizeof(t_arg));
    targ->num_arg = op_tab[opcode - 1].num_arg;
    targ->bytecode = get_bytecodes(
                    tmap,
                    pc_command,
                    opcode);
    if (check_bytecode(opcode, targ->bytecode))
    {
        t_arg_destroy(targ);
        return (NULL);
    }
    targ->arg = read_arg(
                tmap, pc_command,
                opcode, targ->bytecode);
    return (targ);
}

void        t_arg_destroy(t_arg *targ)
{
    if ((targ)->arg)
        free((targ)->arg);
    if ((targ)->bytecode)
        free((targ)->bytecode);
    if ((targ)->bytes_arg)
        free((targ)->bytes_arg);
    free(targ);
}
