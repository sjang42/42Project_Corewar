/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_deal_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:29:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 18:29:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_live(t_map *tmap, int pc_command)
{
	unsigned 	tmp[4];
	int			num;
	int 		i;

	i = 0;
	while (i < 4)
	{
		tmp[i] = get_current_byte(tmap, pc_command + 1 + i);
		i++;
	}
	ft_memcpy(&num, tmp, 4);
	ft_putstr("“A process shows that player ");
	ft_putnbr(num);
	ft_putstr(" is alive”\n");
	return (4);
}

int		deal_ld(t_map *tmap, int pc_command)
{
	unsigned char bytecode;

	bytecode = get_current_byte(tmap, pc_command + 1);

}


int deal_command(int opcode, t_map *tmap, t_champion *tcham)
{

}
