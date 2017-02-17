/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_lldi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 22:11:10 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 22:11:12 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

static int		get_first_arg(t_execute_variable *var)
{
	if (var->targ->bytecode[0] == T_REG)
	{
		if (read_registry(var->tproc->registry, ((char*)(var->targ->arg))[0],
			&(var->type_arg.val_reg[0])))
			return (-1);
		var->type_arg.adr_reg[0] = ((char*)(var->targ->arg))[0];
		var->point += 1;
	}
	else if (var->targ->bytecode[0] == T_DIR)
	{
		ft_memcpy(&(var->type_arg.adr_dir[0]), (char*)(var->targ->arg),
					DIR_ADR_SIZE);
		ft_endian_convert(&(var->type_arg.adr_dir[0]), DIR_ADR_SIZE);
		var->point += 2;
	}
	else
	{
		ft_memcpy(&(var->type_arg.adr_ind[0]),
					(char*)(var->targ->arg), IND_SIZE);
		ft_endian_convert(&(var->type_arg.adr_ind[0]), IND_SIZE);
		var->type_arg.val_ind[0] = (TYPE_IND)read_indirect_data(
		var->tmap, var->pc_command, var->type_arg.adr_ind[0]);
		var->point += 2;
	}
	return (0);
}

static int		get_second_third_arg(t_execute_variable *var)
{
	if (var->targ->bytecode[1] == T_REG)
	{
		if (read_registry(var->tproc->registry,
			*(((char*)(var->targ->arg)) + var->point),
			&(var->type_arg.val_reg[1])))
			return (-1);
		var->type_arg.adr_reg[1] =
			*(((char*)(var->targ->arg)) + var->point);
		var->point += 1;
	}
	else
	{
		ft_memcpy(&(var->type_arg.adr_dir[1]),
					(char*)(var->targ->arg) + var->point,
					DIR_ADR_SIZE);
		ft_endian_convert(&(var->type_arg.adr_dir[1]), DIR_ADR_SIZE);
		var->point += 2;
	}
	var->type_arg.adr_reg[2] = *(((char*)(var->targ->arg)) + var->point);
	var->point += 1;
	return (0);
}

static int		get_val_dir_where(t_execute_variable *var,
								t_arg *targ, t_type_arg *type_arg)
{
	int num1;
	int num2;
	int where;

	if (targ->bytecode[0] == T_REG)
		num1 = type_arg->val_reg[0];
	else if (targ->bytecode[0] == T_DIR)
		num1 = type_arg->adr_dir[0];
	else
		num1 = type_arg->val_ind[0];
	if (targ->bytecode[1] == T_REG)
		num2 = type_arg->val_reg[1];
	else
		num2 = type_arg->adr_dir[1];
	var->type_arg.val_dir[3] = num1 + num2;
	where = ((var->pc_command +
				(var->type_arg.val_dir[3])) % MEM_SIZE);
	where += (where < 0) ? MEM_SIZE : 0;
	return (where);
}

static void		op_commands_lldi(t_arena *tarena, t_execute_variable *var,
								int where)
{
	if (!(tarena->option & COMMANDS))
		return ;
	show_commands_lldi(var->targ, var->type_arg, var->tproc, where);
}

int				deal_lldi(t_arena *tarena, t_map *tmap,
							int pc_command, t_proc *tproc)
{
	t_execute_variable	var;
	int					where;
	void				*tmp;
	int					ret;

	if ((var.targ = get_ret_targ(tmap, &ret, OP_LLDI + 1, pc_command)) == NULL)
		return (ret);
	var.tproc = tproc;
	var.tmap = tmap;
	var.pc_command = pc_command;
	var.point = 0;
	if (get_first_arg(&var) == -1 ||
		get_second_third_arg(&var) == -1)
	{
		t_arg_destroy(var.targ);
		return (ret);
	}
	where = get_val_dir_where(&var, var.targ, &(var.type_arg));
	tmp = read_data(tmap, where, REG_SIZE);
	ft_endian_convert(tmp, REG_SIZE);
	put_registry(tproc->registry, var.type_arg.adr_reg[2], tmp);
	free(tmp);
	op_commands_lldi(tarena, &var, where);
	t_arg_destroy(var.targ);
	return (ret);
}
