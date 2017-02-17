/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_inst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:41:18 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 15:41:19 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static unsigned char	get_bytecode(char **arg)
{
	int				i;
	unsigned char	ret;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		ret = ret << 2;
		if (switch_type(arg[i]) == T_REG)
			ret |= BYTECODE_REG;
		if (switch_type(arg[i]) == T_DIR)
			ret |= BYTECODE_DIR;
		if (switch_type(arg[i]) == T_IND)
			ret |= BYTECODE_IND;
		i++;
	}
	while (i < 4)
	{
		ret = ret << 2;
		i++;
	}
	return (ret);
}

static int				inst_deal_command(char *command, char **arg,
												t_inst *tinst, t_label *tlabel)
{
	int			i;
	char		opcode;
	char		bytecode;
	t_command	tcommand;

	tcommand.command = command;
	tcommand.idx = tinst->size_inst;
	opcode = (char)switch_inst(command);
	t_inst_put(tinst, &opcode, 1);
	if (op_tab[opcode - 1].num_bytecode)
	{
		bytecode = get_bytecode(arg);
		t_inst_put(tinst, &bytecode, 1);
	}
	i = 0;
	while (i < op_tab[opcode - 1].num_arg)
	{
		if (put_one_arg(tcommand, arg[i], tinst, tlabel))
			return (-1);
		i++;
	}
	return (0);
}

/*
**	I already checked the rightness
**	in the get_label.c
**	So I don't have to check again.
*/

t_inst					*get_inst(t_strs *strs, t_label *tlabel)
{
	t_inst	*tinst;
	int		i;
	char	*first;
	char	**arg;
	char	*tmp;

	tinst = t_inst_new(100);
	i = 2;
	while (i < strs->size_strarr)
	{
		first = ft_strdup(strs->strarr[i]);
		if ((tmp = ft_strchr(first, ' ')))
		{
			arg = asm_get_trim_arg(tmp);
			if (inst_deal_command(first, arg, tinst, tlabel) == -1)
			{
				free(first);
				asm_get_destroy_exit(arg, strs, tlabel, tinst);
			}
			ft_destroy_strsplit(arg);
		}
		free(first);
		i++;
	}
	return (tinst);
}
