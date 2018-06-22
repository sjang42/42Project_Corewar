/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_champion_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:24:00 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 00:24:01 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_champion.h>

void            t_champion_destroy(t_champion *tcham)
{
    int idx_proc;
    int i;

    if (!tcham)
        return ;
    if (tcham->tfile.fname)
        free(tcham->tfile.fname);
    if (tcham->tinst.inst)
        free(tcham->tinst.inst);
    idx_proc = 0;
    while (idx_proc < tcham->num_tproc)
    {
        i = 0;
        while (i < REG_NUMBER)
        {
            free(tcham->tproc[idx_proc]->registry[i]);
            i++;
        }
        free(tcham->tproc[idx_proc]->registry);
        idx_proc++;
    }
    if (tcham->tproc)
        free(tcham->tproc);
    free(tcham);
}

void            t_champion_destroy_exit(t_champion *tcham)
{
    t_champion_destroy(tcham);
    ft_exit_error(NULL);
}

void            t_champion_add_proc(t_champion *tcham, int idx_proc,
                                    int pc, int proc_num)
{
    if (tcham->num_tproc + 10 >= tcham->mem_tproc)
    {
        tcham->tproc = (t_proc**)ft_realloc(tcham->tproc,
            sizeof(t_proc*) * tcham->mem_tproc,
            sizeof(t_proc*) * (tcham->mem_tproc + 15));
        tcham->mem_tproc += 15;
    }
    tcham->tproc[tcham->num_tproc] = t_proc_new(pc, tcham->tproc[idx_proc]->carry,
                                    tcham->tproc[idx_proc]->registry,
                                    proc_num);
    // t_proc_put(&(tcham->tproc[tcham->num_tproc]), pc,
                        // tcham->tproc[idx_proc]->carry,
                        // tcham->tproc[idx_proc]->registry);
    tcham->tproc[tcham->num_tproc]->number = proc_num;
    
    tcham->tproc[tcham->num_tproc]->once_lived =
    
        tcham->tproc[idx_proc]->once_lived;
    tcham->num_tproc += 1;
}

int             t_champion_kill_proc(t_champion *tcham, int idx_proc)
{
    int i;

    if (idx_proc >= tcham->num_tproc)
        return (-1);
    i = 0;
    while (i < REG_NUMBER)
    {
        free(tcham->tproc[idx_proc]->registry[i]);
        i++;
    }
    free(tcham->tproc[idx_proc]->registry);
    // free(tcham->tproc[idx_proc]);
    i = idx_proc;
    while (i < tcham->num_tproc - 1)
    {
        tcham->tproc[i] = tcham->tproc[i + 1];
        i++;
    }
    // if (idx_proc + 1 != tcham->num_tproc)
    // {
    //  ft_memmove(tcham->tproc[idx_proc],
    //              tcham->tproc[idx_proc + 1],
    //              sizeof(t_proc) * (tcham->num_tproc - (idx_proc + 1)));
    // }
    (tcham->num_tproc) -= 1;
    return (0);
}
