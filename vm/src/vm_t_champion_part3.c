/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_champion_part3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:24:33 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 00:24:34 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_champion.h>

// void			t_champion_destroy(t_champion **tcham)
// {
// 	int i;

// 	free((*tcham)->tfile.fname);
// 	free((*tcham)->tinst.inst);
// 	i = 0;
// 	while (i < (*tcham)->num_tproc)
// 	{
// 		t_proc_destroy(&((*tcham)->tproc[i]));
// 		i++;
// 	}
// 	free(*tcham);
// 	*tcham = NULL;
// }

void			t_champion_destroy_exit(t_champion *tcham)
{
	t_champion_destroy(tcham);
	ft_exit_error(NULL);
}

void			t_champion_add_proc(t_champion *tcham, int idx_proc, int pc)
{
	if (tcham->num_tproc + 1 >= tcham->mem_tproc)
	{
		tcham->tproc = (t_proc*)ft_realloc(tcham->tproc,
			sizeof(t_proc) * tcham->mem_tproc,
			sizeof(t_proc) * (tcham->mem_tproc + 5));
		tcham->mem_tproc += 5;
	}
	t_proc_put(&(tcham->tproc[tcham->num_tproc]), pc,
				tcham->tproc[idx_proc].carry,
				tcham->tproc[idx_proc].registry);
	tcham->num_tproc += 1;
}

int				t_champion_kill_proc(t_champion *tcham, int idx_proc)
{
	int i;

	if (idx_proc >= tcham->num_tproc)
		return (-1);
	i = 0;
	while (i < REG_NUMBER)
	{
		free(tcham->tproc[idx_proc].registry[i]);
		i++;
	}
	free(tcham->tproc[idx_proc].registry);
	if (idx_proc + 1 != tcham->num_tproc)
		ft_memmove(&(tcham->tproc[idx_proc]),
					&(tcham->tproc[idx_proc + 1]),
					sizeof(t_proc) * (tcham->num_tproc - (idx_proc + 1)));
	(tcham->num_tproc) -= 1;
	return (0);
}
