/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_deal_command_sub1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:04:47 by sjang             #+#    #+#             */
/*   Updated: 2017/02/03 14:04:48 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void	*get_data(t_map *tmap, int pc, size_t size)
{
	char		*ret;
	size_t		i;

	ret = (char*)malloc(sizeof(char) * size);
	i = 0;
	while (i < size)
	{
		ret[i] = get_current_byte(tmap, pc + i);
		i++;
	}
	return ((void*)ret);
}

int		*get_bytecode(t_map *tmap, int pc_command, int num_arg)
{
	int 			*ret;
	unsigned char	bytecode;

	bytecode = get_current_byte(tmap, pc_command + 1);
	ret = (int*)malloc(sizeof(int) * num_arg);
	if (num_arg >= 1)
		ret[0] = bytecode >> 6;
	if (num_arg >= 2)
		ret[1] = (bytecode << 2) >> 6;
	if (num_arg >= 3)
		ret[2] = (bytecode << 4) >> 6;
	return (ret);
}

int		put_registry(char **registry, int idx, long long src)
{
	if (!registry || !*registry ||
		idx < 1 || idx > REG_NUMBER)
		return (0);
	ft_memcpy(registry[idx], src, REG_SIZE);
	return (1);
}

char 	get_current_byte(t_map *tmap, int pc)
{
	return (tmap->map[pc % (MEM_SIZE)]);
}

char	get_indirect_data(t_map *tmap, int pc_command, int idx)
{
	return (get_current_byte(tmap, pc_command + idx));
}

int		check_arg_byte(int opcode, int *arg_byte)
{
	int ret;

	if (!arg_byte)
		return (-1);
	ret = 0;
	if (
		(
			opcode == op_tab[OP_LD].opcode ||
			opcode == op_tab[OP_LLD].opcode
		)
		&&
		(
			(
				arg_byte[0] != T_DIR &&
				arg_byte[0] != T_IND
			)
			||
				arg_byte[1] != T_REG
		)
		)
		ret = -1;
	else if (
				opcode == op_tab[OP_ST].opcode
			&&
				(
						arg_byte[0] != T_REG
					||
					(
						arg_byte[1] != T_REG &&
						arg_byte[1] != T_IND
					)
				)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_ADD].opcode ||
				opcode == op_tab[OP_SUB].opcode)
			&&
			(	
				arg_byte[0] != T_REG ||
				arg_byte[1] != T_REG ||
				arg_byte[2] != T_REG)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_AND].opcode ||
				opcode == op_tab[OP_OR].opcode ||
				opcode == op_tab[OP_XOR].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG &&
					arg_byte[0] != T_DIR &&
					arg_byte[0] != T_IND
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR &&
					arg_byte[1] != T_IND
				)
				||
					arg_byte[2] != T_REG
			)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_LDI].opcode ||
				opcode == op_tab[OP_LLDI].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG &&
					arg_byte[0] != T_DIR &&
					arg_byte[0] != T_IND
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR
				)
				||
					arg_byte[2] != T_REG
			)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_STI].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR
					arg_byte[1] != T_IND
				)
				||
					arg_byte[2] != T_DIR &&
					arg_byte[2] != T_REG
			)
			)
		ret = -1;

	else if (
			(
				opcode == op_tab[OP_LD].opcode
			)
			&&
				(
					(
						arg_byte[0] != T_DIR &&
						arg_byte[0] != T_IND
					)
					||
						arg_byte[1] != T_REG
				)
			)
		ret = -1;
	return (ret);
}