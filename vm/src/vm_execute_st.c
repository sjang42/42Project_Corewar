/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_st.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:12:17 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:12:18 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int	get_first_arg(t_arena *tarena, t_execute_variable *var)
{
	if (read_registry(var->tproc->registry,
		((char*)(var->targ->arg))[0], &(var->type_arg.val_reg[0])))
	{
		return (-1);
	}
	return (0);
}

static int	get_second_arg(t_arena *tarena, t_execute_variable *var,
							int idx_cham)
{
	int where;

	if (var->targ->bytecode[1] == T_REG)
	{
		var->type_arg.adr_reg[1] = ((char*)(var->targ->arg))[1];
		if (put_registry(var->tproc->registry,
			var->type_arg.adr_reg[1], &(var->type_arg.val_reg[0])))
		{
			return (-1);
		}
	}
	else
	{
		ft_memcpy(&(var->type_arg.adr_ind[1]),
					(char*)(var->targ->arg) + 1, IND_SIZE);
		ft_endian_convert(&(var->type_arg.adr_ind[1]), IND_SIZE);
		where = var->pc_command +
				(var->type_arg.adr_ind[1] % IDX_MOD);
		w_sti_reg_to_map(tarena, idx_cham, where, &(var->type_arg.val_reg[0]));
		if (tarena->option & NCURSES)
			ncur_map_update(tarena, where, REG_SIZE);
	}
	return (0);
}

int			deal_st(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc)
{
	t_execute_variable	var;
	int					ret;

	if ((var.targ = get_ret_targ(tmap, &ret, OP_ST + 1,
		tarena->tcham[idx_cham]->tproc[idx_proc].pc)) == NULL)
		return (ret);
	var.tproc = &(tarena->tcham[idx_cham]->tproc[idx_proc]);
	var.tmap = tmap;
	var.pc_command = tarena->tcham[idx_cham]->tproc[idx_proc].pc;
	if (get_first_arg(tarena, &var) == -1 ||
		get_second_arg(tarena, &var, idx_cham) == -1) 
	{
		t_arg_destroy(var.targ);
		return (ret);
	}
	if (tarena->option & COMMANDS)
		show_commands_st(&(tarena->tcham[idx_cham]->tproc[idx_proc]),
						var.targ, var.type_arg.adr_ind[1]);
	t_arg_destroy(var.targ);
	return (ret);
}
