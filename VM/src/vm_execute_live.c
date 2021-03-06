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

static void     vm_show_live(int cham_num)
{
    ft_putstr("“A process shows that player ");
    ft_putnbr(cham_num);
    ft_putstr(" is alive”\n");
}

static int      change_last_live(t_champion **tcham, int num_cham,
                                            int num, int cur_cycle)
{
    int i;

    i = 0;
    while (i < num_cham)
    {
        if (tcham[i]->number == num)
        {
            tcham[i]->last_live = cur_cycle;
            return (i);
        }
        i++;
    }
    return (-1);
}

static void     show_live_update(t_arena *tarena, int idx_cham,
                                            int live_cham, int num)
{
    if (tarena->option & NCURSES)
    {
        info_show_cham_lastlive(tarena->twin->win_info,
                                tarena, live_cham);
        info_show_cham_live_current(tarena->twin->win_info,
                                    tarena, live_cham);
        ncur_show_live(tarena->twin->win_arena, idx_cham, live_cham);
    }
    else if (tarena->option & LIVE)
        vm_show_live(num);
    tarena->last_alive_cham = live_cham;
    tarena->tcham[live_cham]->current_live += 1;
}

int             deal_live(t_arena *tarena, t_map *tmap,
                            int idx_cham, int idx_proc)
{
    t_arg   *targ;
    int     num;
    int     ret;
    int     live_cham;

    tarena->tcham[idx_cham]->tproc[idx_proc]->period_live += 1;
    tarena->tcham[idx_cham]->tproc[idx_proc]->once_lived = 1;
    if ((targ = get_ret_targ(tmap, &ret, OP_LIVE + 1,
            tarena->tcham[idx_cham]->tproc[idx_proc]->pc)) == NULL)
        return (ret);
    ft_memcpy(&num, targ->arg, 4);
    ft_endian_convert(&num, 4);
    num *= -1;
    if (tarena->option & COMMANDS)
        show_commands_live(tarena->tcham[idx_cham]->tproc[idx_proc],
                            num * -1);
    if (num < 0 || num > tarena->num_cham)
    {
        t_arg_destroy(targ);
        return (ret);
    }
    if ((live_cham = change_last_live(tarena->tcham,
                                    tarena->num_cham, num, tarena->cycle))
        != -1)
        show_live_update(tarena, idx_cham, live_cham, num);
    t_arg_destroy(targ);
    return (ret);
}
