/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 22:11:21 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 22:11:22 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_aff(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	targ = t_arg_new(tmap, pc_command, OP_AFF + 1);
	if (targ == NULL)
		return (3);//틀렸을 때 몇 개 반환하는지 보기
	if (read_registry(
		tproc->registry,
		((char*)(targ->arg))[0],
		&(type_arg.val_reg[0])))
	{
		t_arg_destroy(targ);
		return (3);//틀렸을 때 몇 개 반환하는지 보기
	}
	ft_putstr("Aff : ");
	ft_putchar(type_arg.val_reg[0]);
	ft_putstr("\n");
	t_arg_destroy(targ);
	return (3);
}
