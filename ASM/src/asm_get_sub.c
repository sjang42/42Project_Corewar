/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:26:44 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 19:26:45 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int                 check_command(char *command, char **arg)
{
    char    opcode;
    int     i;
    int     type;

    opcode = (char)switch_inst(command);
    if (opcode == 0)
        return (-1);
    i = 0;
    while (arg[i])
        i++;
    if (i != op_tab[opcode - 1].num_arg)
        return (-1);
    i = 0;
    while (arg[i])
    {
        type = switch_type(arg[i]);
        if ((type == 0 || type == T_LAB || type == T_INST)
            ||
            (type & op_tab[opcode - 1].argument[i]) != type)
            return (-1);
        i++;
    }
    return (0);
}

int                 decide_num_byte(char *command, char *arg)
{
    int     type;
    char    opcode;

    opcode = (char)switch_inst(command);
    type = switch_type(arg);
    if (type == T_REG)
        return (1);
    if (type == T_IND)
        return (2);
    if (type == T_DIR && op_tab[opcode - 1].as_address)
        return (2);
    if (type == T_DIR && !op_tab[opcode - 1].as_address)
        return (4);
    return (0);
}

void                asm_get_destroy_exit(char **arg, t_strs *strs,
                                        t_label *tlabel, t_inst *tinst)
{
    ft_destroy_strsplit(arg);
    strs_destroy(strs);
    t_label_destroy(tlabel);
    t_inst_destroy(&tinst);
    ft_exit_error("Syntax error");
}

char                **asm_get_trim_arg(char *tmp)
{
    char    **arg;
    int     j;

    *tmp = 0;
    arg = ft_strsplit(tmp + 1, SEPARATOR_CHAR);
    j = 0;
    while (arg && arg[j])
    {
        tmp = ft_strtrim(arg[j]);
        free(arg[j]);
        arg[j] = tmp;
        j++;
    }
    return (arg);
}
