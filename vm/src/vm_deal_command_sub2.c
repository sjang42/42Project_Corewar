/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_deal_command_sub2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 15:02:35 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 15:02:37 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>


int		count_bytecode_cycle(t_map *tmap, int opcode, int pc_command)
{
	int 			i;
	int 			cycle;
	int 			*part;
	unsigned char	bytecode;

	if (opcode - 1 == OP_LIVE)
		return (4);
	else if (opcode - 1 == OP_ZJMP)
		return (2);
	else if (opcode - 1 == OP_FORK)
		return (2);
	else if (opcode - 1 == OP_LFORK)
		return (2);

	bytecode = read_current_byte(tmap, pc_command + 1);
	part = (int*)malloc(sizeof(int) * op_tab[opcode - 1].num_arg);
	if (op_tab[opcode - 1].num_arg >= 1)
		part[0] = bytecode / 0b1000000;
	if (op_tab[opcode - 1].num_arg >= 2)
		part[1] = bytecode % (0b1000000) / 0b10000;
	if (op_tab[opcode - 1].num_arg >= 3)
		part[2] = bytecode % (0b10000) / 0b100;

	cycle = 0;
	i = 0;
	while (i < op_tab[opcode - 1].num_arg)
	{
		if (part[i] == 0b01)
			cycle += 1;
		else if (part[i] == 0b10 && op_tab[opcode - 1].as_address)
			cycle += 2;
		else if (part[i] == 0b10)
			cycle += 4;
		else if (part[i] == 0b11)
			cycle += 2;
		i++;
	}
	return (cycle);
}


// int		deal_ld(t_map *tmap, int opcode, int pc_command, t_proc *tproc)
// {
// 	void			*arg;
// 	int				i;

	
// 	i = 0;
// 	while (i < op_tab[opcode - 1].num_arg)
// 	{
// 		if (arg_byte[i] == T_DIR)
// 		{

// 		}
// 	}




// }