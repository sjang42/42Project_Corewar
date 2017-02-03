/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:22:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 15:22:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_proc.h>
#include <op.h>

t_proc			*t_proc_new(int pc, int carry, int num, char **registry)
{
	t_proc	*tproc;
	int		i;

	tproc = (t_proc*)malloc(sizeof(t_proc));
	tproc->pc = pc;
	tproc->carry = carry;
	tproc->registry = (char**)malloc(sizeof(char*) * REG_NUMBER);
	tproc->on_command = 0;
	tproc->wait_cycle= 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		tproc->registry[i] = (char*)malloc(sizeof(char) * REG_SIZE);
		if (registry)
			ft_memcpy(tproc->registry[i], registry[i], REG_SIZE);
		else
			ft_bzero(tproc->registry[i], REG_SIZE);
		i++;
	}
	if (!registry)
		ft_memcpy(tproc->registry[0], &num, REG_SIZE);
	return (tproc);
}

void			t_proc_destroy(t_proc tproc)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		free(tproc.registry[i]);
		i++;
	}
	free(tproc.registry);
}
