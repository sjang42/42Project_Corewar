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

int				read_registry(char **registry, int idx, void *dest)
{
	if (idx <= 0 || idx > REG_NUMBER)
		return (-1);
	ft_memcpy(dest, registry[idx], REG_SIZE);
	return (0);
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