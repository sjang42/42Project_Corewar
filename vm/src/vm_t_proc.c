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

t_proc			*t_proc_new(int pc, int carry, char **registry, int proc_num)
{
	t_proc	*tproc;

	tproc = (t_proc*)malloc(sizeof(t_proc));
	t_proc_put(tproc, pc, carry, registry);
	tproc->number = proc_num;
	return (tproc);
}

void			t_proc_put(t_proc *tproc, int pc, int carry, char **registry)
{
	int		i;

	tproc->pc = pc;
	tproc->carry = carry;
	tproc->registry = (char**)malloc(sizeof(char*) * (REG_NUMBER));
	tproc->on_command = 0;
	tproc->wait_cycle = 0;
	tproc->just_born = 1;
	tproc->period_born = 1;
	tproc->once_lived = 0;
	// if (registry)
	// 	tproc->period_live = 1;
	// else
		tproc->period_live = 0;
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
}

void			t_proc_destroy(t_proc *tproc)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		free(tproc->registry[i]);
		i++;
	}
	free(tproc->registry);
	free(tproc);
}

int 			t_proc_find_minproc(t_arena *tarena, int min,
									int *idx_cham_store, int *idx_proc_store)
{
	int success;
	int idx_cham;
	int idx_proc;
	int num_proc;

	success = 0;
	while (!success)
	{
		idx_cham = 0;
		while (idx_cham < tarena->num_cham)
		{
			idx_proc = 0;
			while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
			{
				if (tarena->tcham[idx_cham]->tproc[idx_proc].number == min)
				{
					success = 1;
					break ;
				}
				idx_proc++;
			}
			if (success)
				break ;
			idx_cham++;
		}
		min++;
	}
	*idx_cham_store = idx_cham;
	*idx_proc_store = idx_proc;
	return (min);
}

int 			t_proc_find_maxproc(t_arena *tarena, int max,
									int *idx_cham_store, int *idx_proc_store)
{
	int success;
	int idx_cham;
	int idx_proc;
	int num_proc;

	success = 0;
	while (!success)
	{
		idx_cham = 0;
		while (idx_cham < tarena->num_cham)
		{
			idx_proc = 0;
			while (idx_proc < tarena->tcham[idx_cham]->num_tproc)
			{
				if (tarena->tcham[idx_cham]->tproc[idx_proc].number == max &&
					tarena->tcham[idx_cham]->tproc[idx_proc].just_born != 1)
				{
					success = 1;
					break ;
				}
				idx_proc++;
			}
			if (success)
				break ;
			idx_cham++;
		}
		max--;
	}
	*idx_cham_store = idx_cham;
	*idx_proc_store = idx_proc;
	return (max);
}























