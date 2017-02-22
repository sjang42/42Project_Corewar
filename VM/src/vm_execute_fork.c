/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:06:39 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 21:06:40 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_fork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;
	int				where;

	if ((targ = get_ret_targ(tarena->tmap, &ret,
				OP_FORK + 1, pc_command)) == NULL)
		return (ret);
	ft_memcpy(&(type_arg.adr_dir[0]), (char*)(targ->arg), DIR_ADR_SIZE);
	ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
	if (tarena->option & COMMANDS)
		show_commands_fork(tarena->tcham[idx_cham]->tproc[idx_proc],
				type_arg,
				(pc_command + (type_arg.adr_dir[0] % IDX_MOD)) % MEM_SIZE);
	type_arg.adr_dir[0] %= IDX_MOD;
	where = (pc_command + type_arg.adr_dir[0]) % MEM_SIZE;
	where += (where < 0) ? MEM_SIZE : 0;
	tarena->num_process += 1;
	t_order_store(tarena->torder, idx_cham,
					tarena->tcham[idx_cham]->num_tproc);
	t_champion_add_proc(tarena->tcham[idx_cham], idx_proc, where,
						tarena->used_proc_num);
	tarena->used_proc_num += 1;
	if (tarena->option & NCURSES)
		info_show_process(tarena->twin->win_info, tarena->num_process);
	t_arg_destroy(targ);
	return (ret);
}
