/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:12:44 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 18:12:46 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		get_current_byte(t_map *tmap, int pc)
{
	return (tmap->map[pc % (MEM_SIZE)]);
}

int		is_opcode(char byte)
{
	if (byte >= 1 && byte <= 16)
		return (1);
	else
		return (0);
}

int		get_cycle(int opcode)
{
	return (op_tab[opcode - 1].num_cycle);
}

int		(t_map *tmap, t_champion *tcham)
{
	int cur_byte;

	if (!(tcham->tproc.on_command))
	{
		cur_byte = get_current_byte(tmap, tcham->tproc.pc)
		if (is_opcode(cur_byte))
		{
			tcham->tproc.on_command = cur_byte;
			tcham->tproc.wait_cycle = get_cycle(cur_byte);

		}
		else
		{

		}
	}
	else
	{
		if (tcham->tproc.wait_cycle == 1)
		{

		}
		else
		{

		}
	}
}
