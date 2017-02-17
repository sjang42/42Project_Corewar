/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_sti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 17:08:36 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 17:08:38 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int		get_first_arg(t_execute_variable *var)
{
	if (read_registry(var->tproc->registry, ((char*)(var->targ->arg))[0],
		&(var->type_arg.val_reg[0])))
	{
		return (-1);
	}
	var->point = 1;
	return (0);
}

static int		get_second_arg(t_execute_variable *var, t_arena *tarena)
{
	if (var->targ->bytecode[1] == T_REG)
	{
		if (read_registry(var->tproc->registry, ((char*)(var->targ->arg))[1],
			&(var->type_arg.val_reg[1])))
			return (-1);
		var->type_arg.adr_reg[1] = ((char*)(var->targ->arg))[1];
		var->point += 1;
	}
	else if (var->targ->bytecode[1] == T_DIR)
	{
		ft_memcpy(&(var->type_arg.adr_dir[1]),
		(char*)(var->targ->arg) + 1, DIR_ADR_SIZE);
		ft_endian_convert(&(var->type_arg.adr_dir[1]), DIR_ADR_SIZE);
		var->point += 2;
	}
	else
	{
		ft_memcpy(&(var->type_arg.adr_ind[1]),
				(char*)(var->targ->arg) + 1, IND_SIZE);
		ft_endian_convert(&(var->type_arg.adr_ind[1]), IND_SIZE);
		var->type_arg.val_ind[1] = (TYPE_IND)read_indirect_data(
		tarena->tmap, var->pc_command, var->type_arg.adr_ind[1] % IDX_MOD);
		var->point += 2;
	}
	return (0);
}

static int		get_third_arg(t_execute_variable *var)
{
	if (var->targ->bytecode[2] == T_REG)
	{
		if (read_registry(var->tproc->registry,
			*(((char*)(var->targ->arg)) + var->point),
			&(var->type_arg.val_reg[2])))
		{
			return (-1);
		}
		var->point += 1;
	}
	else
	{
		ft_memcpy(&(var->type_arg.adr_dir[2]),
					(char*)(var->targ->arg) + var->point,
					DIR_ADR_SIZE);
		ft_endian_convert(&(var->type_arg.adr_dir[2]), DIR_ADR_SIZE);
		var->point += 2;
	}
	return (0);
}

static int		get_val_dir_where(t_execute_variable *var)
{
	int num1;
	int num2;
	int where;

	if (var->targ->bytecode[1] == T_REG)
		num1 = var->type_arg.val_reg[1];
	else if (var->targ->bytecode[1] == T_DIR)
		num1 = var->type_arg.adr_dir[1];
	else
		num1 = var->type_arg.val_ind[1];
	if (var->targ->bytecode[2] == T_REG)
		num2 = var->type_arg.val_reg[2];
	else
		num2 = var->type_arg.adr_dir[2];
	var->type_arg.val_dir[3] = num1 + num2;
	where = var->pc_command + (var->type_arg.val_dir[3] % IDX_MOD);
	if (where < 0)
		where += (MEM_SIZE);
	return (where);
}

int				deal_sti(t_arena *tarena, t_map *tmap,
							int idx_cham, int idx_proc)
{
	t_execute_variable	var;
	int					ret;
	int					where;

	if ((var.targ = get_ret_targ(tmap, &ret, OP_STI + 1,
		tarena->tcham[idx_cham]->tproc[idx_proc].pc)) == NULL)
		return (ret);
	var.pc_command = tarena->tcham[idx_cham]->tproc[idx_proc].pc;
	var.tproc = &(tarena->tcham[idx_cham]->tproc[idx_proc]);
	var.tmap = tmap;
	var.point = 0;
	if (get_first_arg(&var) == -1 || get_second_arg(&var, tarena) == -1 ||
		get_third_arg(&var) == -1)
	{
		t_arg_destroy(var.targ);
		return (ret);
	}
	where = get_val_dir_where(&var);
	w_sti_reg_to_map(tarena, idx_cham, where, &(var.type_arg.val_reg[0]));
	if (tarena->option & NCURSES)
		ncur_map_update(tarena, where, REG_SIZE);
	if (tarena->option & COMMANDS)
		show_commands_sti(var.targ, var.type_arg, var.tproc, where);
	t_arg_destroy(var.targ);
	return (ret);
}
