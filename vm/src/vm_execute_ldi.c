/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_ldi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:06:30 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 21:06:32 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_ldi(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				where;
	void			*tmp;
	int				ret;

	targ = t_arg_new(tmap, pc_command, OP_LDI + 1);
	if (targ == NULL)
		return (5);
	ret = 0;

	/*
	**	get 1st arg
	*/
	if (targ->bytecode[0] == T_REG)			//get : type_arg.val_reg[0]
	{
		if (read_registry(
			tproc->registry,
			((char*)(targ->arg))[0],
			&(type_arg.val_reg[0])))
		{
			t_arg_destroy(targ);
			return (5);//틀렸을 때 몇 개 반환하는지 보기
		}
		type_arg.adr_reg[0] = ((char*)(targ->arg))[0];
		ret += 1;
	}
	else if (targ->bytecode[0] == T_DIR)	//get : type_arg.adr_dir[0]
	{
		ft_memcpy(&(type_arg.adr_dir[0]),
					(char*)(targ->arg),
					DIR_ADR_SIZE);
		ft_endian_convert(&(type_arg.adr_dir[0]), DIR_ADR_SIZE);
		ret += 2;
	}
	else//T_IND								//get : type_arg.val_ind[0]
	{
		ft_memcpy(&(type_arg.adr_ind[0]), (char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[0]), IND_SIZE);
		type_arg.val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg.adr_ind[0] % IDX_MOD);
		ret += 2;
	}


	/*
	**	get 2nd arg
	*/
	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[1]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg)) + ret),
			&(type_arg.val_reg[1])))
		{
			t_arg_destroy(targ);
			return (5);//틀렸을 때 몇 개 반환하는지 보기
		}
		type_arg.adr_reg[1] = *(((char*)(targ->arg)) + ret);
		ret += 1;
	}
	else						//T_DIR		//get : type_arg.adr_dir[1]
	{
		ft_memcpy(&(type_arg.adr_dir[1]),
					(char*)(targ->arg) + ret,
					DIR_ADR_SIZE);
		ft_endian_convert(&(type_arg.adr_dir[1]), DIR_ADR_SIZE);
		ret += 2;
	}

	/*
	** get 3rd arg
	*/
	type_arg.adr_reg[2] = *(((char*)(targ->arg)) + ret);
	ret += 1;

	/*
	**	process ldi
	*/
	if (targ->bytecode[1] == T_REG)
	{
		if (targ->bytecode[0] == T_REG)
			type_arg.val_dir[3] = type_arg.val_reg[0] + type_arg.val_reg[1];
		else if (targ->bytecode[0] == T_DIR)
			type_arg.val_dir[3] = type_arg.adr_dir[0] + type_arg.val_reg[1];
		else //targ->bytecode[0] == T_IND
			type_arg.val_dir[3] = type_arg.val_ind[0] + type_arg.val_reg[1];
	}
	else //(targ->bytecode[1] == T_DIR)
	{
		if (targ->bytecode[0] == T_REG)
			type_arg.val_dir[3] = type_arg.val_reg[0] + type_arg.adr_dir[1];
		else if (targ->bytecode[0] == T_DIR)
			type_arg.val_dir[3] = type_arg.adr_dir[0] + type_arg.adr_dir[1];
		else //targ->bytecode[0] == T_IND
			type_arg.val_dir[3] = type_arg.val_ind[0] + type_arg.adr_dir[1];
	}

	where = ((pc_command + type_arg.val_dir[3]) % MEM_SIZE);
	tmp = read_data(tmap, where, REG_SIZE);
	ft_endian_convert(tmp, REG_SIZE);
	put_registry(tproc->registry, type_arg.adr_reg[2], tmp);
	free(tmp);
	t_arg_destroy(targ);
	return (ret + 2);
}
