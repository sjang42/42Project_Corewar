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

void            t_proc_put(t_proc *tproc, int pc, int carry, char **registry)
{
    int     i;

    tproc->pc = pc;
    tproc->carry = carry;
    tproc->registry = (char**)malloc(sizeof(char*) * (REG_NUMBER));
    tproc->on_command = 0;
    tproc->wait_cycle = 0;
    tproc->just_born = 1;
    tproc->once_lived = 0;
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

t_proc          *t_proc_new(int pc, int carry, char **registry, int proc_num)
{
    t_proc  *tproc;

    tproc = (t_proc*)malloc(sizeof(t_proc));
    t_proc_put(tproc, pc, carry, registry);
    tproc->number = proc_num;
    return (tproc);
}

void            t_proc_destroy(t_proc *tproc)
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

static int      have_max(t_champion *tcham, int max)
{
    int idx_proc;

    idx_proc = 0;
    while (idx_proc < tcham->num_tproc)
    {
        if (tcham->tproc[idx_proc]->number == max &&
            tcham->tproc[idx_proc]->just_born != 1)
            return (idx_proc);
        idx_proc++;
    }
    return (-1);
}

int             t_proc_find_maxproc(t_arena *tarena, int max,
                                    int *idx_cham_store, int *idx_proc_store)
{
    int success;
    int idx_cham;
    int idx_proc;

    success = 0;
    while (!success)
    {
        idx_cham = 0;
        while (idx_cham < tarena->num_cham)
        {
            if ((idx_proc = have_max(tarena->tcham[idx_cham], max)) != -1)
            {
                success = 1;
                break ;
            }
            idx_cham++;
        }
        max--;
    }
    *idx_cham_store = idx_cham;
    *idx_proc_store = idx_proc;
    return (max);
}
