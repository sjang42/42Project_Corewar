/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_inst_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:34:13 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 19:34:16 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int      deal_t_dir(char *arg, char *mem,
                            t_label *tlabel, t_command tcommand)
{
    int tmp;
    int num_byte;

    num_byte = decide_num_byte(tcommand.command, arg);
    if (is_direct(arg) == 1)
        tmp = ft_atoi(arg + 1);
    else
    {
        tmp = t_label_get_idx(tlabel, arg + 2);
        if (tmp == -1)
            return (-1);
        tmp = tmp - tcommand.idx;
    }
    ft_memcpy(mem, &tmp, num_byte);
    ft_endian_convert(mem, num_byte);
    return (0);
}

static int      deal_t_ind(char *arg, char *mem,
                            t_label *tlabel, t_command tcommand)
{
    int tmp;
    int num_byte;

    num_byte = decide_num_byte(tcommand.command, arg);
    if (is_indirect(arg) == 1)
        tmp = ft_atoi(arg);
    else
    {
        tmp = t_label_get_idx(tlabel, arg + 1);
        if (tmp == -1)
            return (-1);
        tmp = tmp - tcommand.idx;
    }
    ft_memcpy(mem, &tmp, 2);
    ft_endian_convert(mem, num_byte);
    return (0);
}

/*
**  if (is_direct(arg) == 1) || if (is_direct(arg) == 1) --> just number
**  if (is_direct(arg) == 2) || if (is_direct(arg) == 2) --> label
*/

int             put_one_arg(t_command tcommand, char *arg,
                            t_inst *tinst, t_label *tlabel)
{
    char    *mem;
    int     num_byte;
    int     type;

    num_byte = decide_num_byte(tcommand.command, arg);
    mem = (char*)malloc(sizeof(char) * num_byte);
    ft_bzero(mem, num_byte);
    type = switch_type(arg);
    if (type == T_REG)
        mem[0] = (char)is_register(arg);
    if ((type == T_DIR && deal_t_dir(arg, mem, tlabel, tcommand) == -1) ||
        (type == T_IND && deal_t_ind(arg, mem, tlabel, tcommand) == -1))
    {
        free(mem);
        return (-1);
    }
    t_inst_put(tinst, mem, num_byte);
    free(mem);
    return (0);
}
