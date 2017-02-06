/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_live.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:13:17 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:13:18 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_live(t_map *tmap, int pc_command)
{
	t_arg	*targ;
	int		num;
	int		i;

	i = 0;
	targ = t_arg_new(tmap, pc_command, OP_LIVE + 1);
	if (targ == NULL)
		return (5);//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
	ft_memcpy(&num, targ->arg, 4);
	ft_endian_convert(&num, 4);
	if (num < 0)//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
		return (5);
	ft_putstr("“A process shows that player ");
	ft_putnbr(num);
	ft_putstr(" is alive”\n");
	t_arg_destroy(targ);
	return (5);
}
