/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena_checkup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:23:46 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 22:23:47 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_arena.h>

static void     kill_proc(t_arena *tarena, int idx_cham, int idx_proc)
{
    tarena->num_process -= 1;
    if (tarena->option & NCURSES)
    {
        info_show_process(tarena->twin->win_info, tarena->num_process);
        ncur_unhighlight_pc(tarena->twin->win_arena, tarena->tmap,
            tarena->tcham[idx_cham]->tproc[idx_proc],
            tarena);
    }
    t_champion_kill_proc(tarena->tcham[idx_cham], idx_proc);
    t_order_delete(tarena->torder, idx_cham, idx_proc);
}

static int      init_proc(t_arena *tarena, int idx_cham, int idx_proc)
{
    tarena->tcham[idx_cham]->tproc[idx_proc]->period_live = 0;
    tarena->tcham[idx_cham]->tproc[idx_proc]->once_lived = 0;
    return (1);
}

void            checkup_proc(t_arena *tarena)
{
    int idx_cham;
    int idx_proc;
    int num_tproc;
    int i;

    idx_cham = 0;
    while (idx_cham < tarena->num_cham)
    {
        i = 0;
        idx_proc = 0;
        num_tproc = tarena->tcham[idx_cham]->num_tproc;
        while (i < num_tproc)
        {
            if (tarena->tcham[idx_cham]->tproc[idx_proc]->once_lived == 0)
                kill_proc(tarena, idx_cham, idx_proc);
            else
                idx_proc += init_proc(tarena, idx_cham, idx_proc);
            i++;
        }
        if (tarena->option & NCURSES)
            info_show_cham_live_current(tarena->twin->win_info,
                                        tarena, idx_cham);
        tarena->tcham[idx_cham]->current_live = 0;
        idx_cham++;
    }
}
