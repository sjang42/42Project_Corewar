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

int					check_command(char *command, char **arg)
{
	char opcode;
	int i;
	int type;

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
		if ((type== 0 || type == T_LAB || type == T_INST)
			||
			(type & op_tab[opcode - 1].argument[i]) != type)
			return (-1);
		i++;
	}
	return (0);
}

int					decide_num_byte(char *command, char *arg)
{
	int type;
	char opcode;

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

unsigned char		get_bytecode(char **arg)
{
	int i;
	unsigned char ret;

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

/*
**	if (is_direct(arg) == 1) || if (is_direct(arg) == 1) --> just number
**	if (is_direct(arg) == 2) || if (is_direct(arg) == 2) --> label
*/
int		put_one_arg(t_command tcommand, char *arg,
						t_inst *tinst, t_label *tlabel)
{
	char	*mem;
	int		num_byte;
	int		type;
	int		opcode;
	int		tmp;
	int		idx;

	num_byte = decide_num_byte(tcommand.command, arg);
	mem = (char*)malloc(sizeof(char) * num_byte);
	ft_bzero(mem, num_byte);
	type = switch_type(arg);
	opcode = switch_inst(tcommand.command);
	if (type == T_REG)
		mem[0] = (char)is_register(arg);
	if (type == T_DIR)
	{
		if (is_direct(arg) == 1)
			tmp = ft_atoi(arg + 1);
		else
		{
			tmp = t_label_get_idx(tlabel, arg + 2);
			if (tmp == -1)
			{
				free(mem);
				return (-1);
			}
			tmp = tmp - tcommand.idx;
		}
		ft_memcpy(mem, &tmp, num_byte);
		ft_endian_ltob(mem, num_byte);
	}
	if (type == T_IND)
	{
		if (is_indirect(arg) == 1)
			tmp = ft_atoi(arg);
		else
		{
			tmp = t_label_get_idx(tlabel, arg + 1);
			if (tmp == -1)
			{
				free(mem);
				return (-1);
			}
			tmp = tmp - tcommand.idx;
		}
		ft_memcpy(mem, &tmp, 2);
		ft_endian_ltob(mem, num_byte);
	}
	t_inst_put(tinst, mem, num_byte);
	free(mem);
	return (0);
}

int			deal_command(char *command, char **arg,
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
t_inst			*get_inst(t_strs *strs, t_label *tlabel)
{
	t_inst	*tinst;
	int		i;
	int		j;
	char	*first;
	char	**arg;
	char	*tmp;

	tinst = t_inst_new(100);
	i = 2;
	while (i < strs->size_strarr)
	{
		first = ft_strdup(strs->strarr[i]);
		if (switch_type(first) == T_LAB)
			;
		else if ((tmp = ft_strchr(first, ' ')))
		{
			*tmp = 0;
			arg = ft_strsplit(tmp + 1, SEPARATOR_CHAR);
			j = 0;
			while (arg[j])
			{
				tmp = ft_strtrim(arg[j]);
				free(arg[j]);
				arg[j] = tmp;
				j++;
			}
			if (deal_command(first, arg, tinst, tlabel))
			{
				free(first);
				// ft_destroy_strsplit(arg);
				strs_destroy(strs);
				t_label_destroy(tlabel);
				t_inst_destroy(&tinst);
				ft_exit_error("Syntax error3");
			}
			ft_destroy_strsplit(arg);
		}
		free(first);
		i++;
	}
	return (tinst);
}
