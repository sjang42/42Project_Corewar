/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:12:44 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 18:12:46 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int      is_opcode(char byte)
{
    if (byte >= MIN_OPCODE && byte <= MAX_OPCODE)
        return (1);
    else
        return (0);
}

static int      get_cycle(int opcode)
{
    return (op_tab[opcode - 1].num_cycle);
}

static int      start_command(t_map *tmap, int idx_cham,
                            t_arena *tarena, int idx_proc)
{
    int     cur_byte;

    cur_byte = read_current_byte(tmap,
                    tarena->tcham[idx_cham]->tproc[idx_proc]->pc);
    if (is_opcode(cur_byte))
    {
        tarena->tcham[idx_cham]->tproc[idx_proc]->on_command = cur_byte;
        tarena->tcham[idx_cham]->tproc[idx_proc]->wait_cycle =
                                                get_cycle(cur_byte) - 1;
        return (0);
    }
    else
        return (1);
}

static int      finish_command(t_map *tmap, int idx_cham,
                                t_arena *tarena, int idx_proc)
{
    int ret;

    if (tarena->tcham[idx_cham]->tproc[idx_proc]->wait_cycle == 1)
{
        ret = deal_command(tmap, idx_cham, idx_proc, tarena);
        tarena->tcham[idx_cham]->tproc[idx_proc]->on_command = 0;
        return (ret);
    }
    else
    {
        (tarena->tcham[idx_cham]->tproc[idx_proc]->wait_cycle) -= 1;
        return (0);
    }
}

int             vm_execute_proc(t_map *tmap, int idx_cham,
                                t_arena *tarena, int idx_proc)
{
    if (!(tarena->tcham[idx_cham]->tproc[idx_proc]->on_command))
    {
        return (start_command(tmap, idx_cham, tarena, idx_proc));
    }
    else
    {
        return (finish_command(tmap, idx_cham, tarena, idx_proc));
    }
}
