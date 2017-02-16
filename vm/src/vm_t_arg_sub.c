/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arg_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:18:38 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 17:18:39 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arg.h>
#include <stdio.h>//

static int		get_size_arg(int opcode, int *arg_byte)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (i < op_tab[opcode - 1].num_arg)
	{
		if (arg_byte[i] == T_DIR && !(op_tab[opcode - 1].as_address))
			ret += 4;
		else if (arg_byte[i] == T_DIR)
			ret += 2;
		else if (arg_byte[i] == T_IND)
			ret += 2;
		else if (arg_byte[i] == T_REG)
			ret += 1;
		i++;
	}
	return (ret);
}

static int		*get_bytes_arg(int opcode, int *bytecode, int num_arg)
{
	int *bytes_arg;
	int	i;

	bytes_arg = (int*)malloc(sizeof(int) * num_arg);
	i = 0;
	while (i < num_arg)
	{
		if (bytecode[i] == T_DIR && !(op_tab[opcode - 1].as_address))
			bytes_arg[i] = 4;
		else if (bytecode[i] == T_DIR)
			bytes_arg[i] = 2;
		else if (bytecode[i] == T_IND)
			bytes_arg[i] = 2;
		else if (bytecode[i] == T_REG)
			bytes_arg[i] = 1;
		i++;
	}
	return (bytes_arg);
}

void		*read_arg(t_map *tmap, int pc_command,
									int opcode, int *bytecode)
{
	void	*arg;
	int		where;
	int		size_arg;
	int		i;

	where = 0;
	size_arg = get_size_arg(opcode, bytecode);
	if (op_tab[opcode - 1].num_bytecode)
		where += 1;
	arg = read_data(tmap, pc_command + 1 + where, size_arg);
	return (arg);
}

int			*read_bytecode(t_map *tmap, int pc_command, int num_arg)
{
	int 			*ret;
	unsigned char	bytecode;
	int				i;

	bytecode = read_current_byte(tmap, pc_command + 1);
	ret = (int*)malloc(sizeof(int) * num_arg);
	if (num_arg >= 1)
		ret[0] = bytecode / 0b1000000;
	if (num_arg >= 2)
		ret[1] = bytecode % (0b1000000) / 0b10000;
	if (num_arg >= 3)
		ret[2] = bytecode % (0b10000) / 0b100;

	i = 0;
	while (i < num_arg)
	{
		if (ret[i] == 0b01)
			ret[i] = T_REG;
		else if (ret[i] == 0b10)
			ret[i] = T_DIR;
		else if (ret[i] == 0b11)
			ret[i] = T_IND;
		i++;
	}
	return (ret);
}

int		check_bytecode(int opcode, int *bytecode)
{
	int i;

	if (!bytecode)
		return (-1);
	i = 0;
	while (i < op_tab[opcode - 1].num_arg)
	{
		if (!(bytecode + i))
			return (-1);
		if (bytecode[i] == 0)
			return (-1);
		if ((bytecode[i] & op_tab[opcode - 1].argument[i]) != bytecode[i])
			return (-1);
		i++;
	}
	return (0);
}
