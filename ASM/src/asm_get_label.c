/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:53:52 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 18:53:53 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void         fill_one_arg(char *command, char *arg, t_inst *tinst)
{
    char    mem[4];
    int     num_byte;

    ft_bzero(mem, 4);
    num_byte = decide_num_byte(command, arg);
    t_inst_put(tinst, mem, num_byte);
}

static int          fill_command(char *command, char **arg, t_inst *tinst)
{
    int     i;
    char    opcode;
    char    zero;

    zero = 0;
    if (check_command(command, arg))
        return (-1);
    opcode = (char)switch_inst(command);
    t_inst_put(tinst, &zero, 1);
    if (op_tab[opcode - 1].num_bytecode)
        t_inst_put(tinst, &zero, 1);
    i = 0;
    while (i < op_tab[opcode - 1].num_arg)
    {
        fill_one_arg(command, arg[i], tinst);
        i++;
    }
    return (0);
}

static void         label_deal_error(t_label_variable var,
                                        t_label *tlabel, t_strs *tstrs)
{
    free(var.first);
    asm_get_destroy_exit(var.arg, tstrs, tlabel, var.tinst);
}

t_label             *get_label(t_strs *tstrs)
{
    t_label             *tlabel;
    t_label_variable    var;

    var.tinst = t_inst_new(100);
    tlabel = t_label_new(100);
    var.i = 2;
    while (var.i < tstrs->size_strarr)
    {
        var.first = ft_strdup(tstrs->strarr[var.i]);
        if (switch_type(var.first) == T_LAB)
            t_label_put(tlabel, var.first, var.tinst->size_inst);
        else if ((var.tmp = ft_strchr(var.first, ' ')))
        {
            var.arg = asm_get_trim_arg(var.tmp);
            if (!var.arg || fill_command(var.first, var.arg, var.tinst) == -1)
                label_deal_error(var, tlabel, tstrs);
            ft_destroy_strsplit(var.arg);
        }
        else
            label_deal_error(var, tlabel, tstrs);
        free(var.first);
        var.i += 1;
    }
    t_inst_destroy(&(var.tinst));
    return (tlabel);
}
