/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_commands_part4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:12:22 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 18:12:23 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void		show_commands_live(t_proc *tproc, int num)
{
	printf("P%5d | ", tproc->number + 1);
	printf("live %d\n", num);
}

void		show_commands_aff(t_proc *tproc, t_arg *targ)
{
	printf("P%5d | ", tproc->number + 1);
	printf("aff r%d\n", ((char*)(targ->arg))[0]);
}

void		show_commands_sub(t_proc *tproc, t_arg *targ)
{
	printf("P%5d | ", tproc->number + 1);
	printf("sub r%d r%d r%d\n", ((char*)(targ->arg))[0],
			((char*)(targ->arg))[1], ((char*)(targ->arg))[2]);
}

void		show_commands_add(t_proc *tproc, t_arg *targ)
{
	printf("P%5d | ", tproc->number + 1);
	printf("and r%d r%d r%d\n", ((char*)(targ->arg))[0],
			((char*)(targ->arg))[1], ((char*)(targ->arg))[2]);
}
