/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_and_arg12.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 01:53:32 by sjang             #+#    #+#             */
/*   Updated: 2017/02/16 01:53:33 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		and_arg1_reg_dir(t_proc *tproc, t_arg *targ,
						t_type_arg *type_arg)
{
	if (targ->bytecode[0] == T_REG)			//get : type_arg.val_reg[i]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg))),
			&(type_arg->val_reg[0])))
			return (-1);
		return (1);
	}
	else if (targ->bytecode[0] == T_DIR)	//get : type_arg.val_dir[i]
	{
		ft_memcpy(&(type_arg->val_dir[0]),
					(char*)(targ->arg),
					DIR_SIZE);
		ft_endian_convert(&(type_arg->val_dir[0]), DIR_SIZE);
		return (4);
	}
	return (0);
}

int		and_arg1_ind(t_arg *targ, t_type_arg *type_arg,
						t_map *tmap, int pc_command)
{
	if (targ->bytecode[0] == T_IND)
	{
		ft_memcpy(&(type_arg->adr_ind[0]),
					(char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg->adr_ind[0]), IND_SIZE);
		type_arg->val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg->adr_ind[0] % IDX_MOD);
		return (2);
	}
	return (0);
}

int		and_arg2_reg_dir(t_proc *tproc, t_arg *targ,
						t_type_arg *type_arg, int point)
{
	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[i]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg)) + point),
			&(type_arg->val_reg[1])))
			return (-1);
		return (1);
	}
	else if (targ->bytecode[1] == T_DIR)	//get : type_arg.val_dir[i]
	{
		ft_memcpy(&(type_arg->val_dir[1]),
					(char*)(targ->arg) + point,
					DIR_SIZE);
		ft_endian_convert(&(type_arg->val_dir[1]), DIR_SIZE);
		return (4);
	}
	return (0);
}

int		and_arg2_ind(t_arg *targ, t_type_arg *type_arg,
					t_map *tmap, int pc_command)
{
	if (targ->bytecode[1] == T_IND)
	{
		ft_memcpy(&(type_arg->adr_ind[1]),
					(char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg->adr_ind[1]), IND_SIZE);
		type_arg->val_ind[1] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg->adr_ind[1] % IDX_MOD);
		return (2);
	}
	return (0);
}

int		and_arg123(t_execute_variable *var)
{
	int point[3];

	if (var->targ->bytecode[0] == T_REG ||
		var->targ->bytecode[0] == T_DIR)
		point[0] = and_arg1_reg_dir(var->tproc, var->targ, var->type_arg);
	else
		point[0] = and_arg1_ind(var->targ, var->type_arg, var->tmap, var->pc_command);
	if (point[0] == -1)
		return (-1);
	if (var->targ->bytecode[1] == T_REG ||
		var->targ->bytecode[1] == T_DIR)
		point[1] = and_arg2_reg_dir(var->tproc, var->targ, var->type_arg, point[0]);
	else
		point[1] = and_arg2_ind(var->targ, var->type_arg, var->tmap, var->pc_command);
	if (point[1] == -1)
		return (-1);
	point[2] = point[0] + point[1];
	var->type_arg->adr_reg[2] = *(((char*)(var->targ->arg)) + point[2]);
	point[2] += 1;
	return (point[2]);
}
