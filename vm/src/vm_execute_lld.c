/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_lld.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 22:11:02 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 22:11:04 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_lld(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ft_bzero(&type_arg, sizeof(t_type_arg));
	targ = t_arg_new(tmap, pc_command, OP_LLD + 1);
	if (targ == NULL)
		return (5);//틀렸을 때 몇 개 반환하는지 보기
	ret = 0;

	/*
	** get 1st arg
	*/
	if (targ->bytecode[0] == T_DIR)				//get : type_arg.val_dir[0]
	{
		ft_memcpy(&(type_arg.val_dir[0]),
					(char*)(targ->arg),
					DIR_SIZE);
		ft_endian_convert(&(type_arg.val_dir[0]), DIR_SIZE);
		ret += 4;
	}
	else//(targ->bytecode[0] == T_IND)			//get : type_arg.val_ind[0]
	{
		ft_memcpy(&(type_arg.adr_ind[0]), (char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[0]), IND_SIZE);
		type_arg.val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg.adr_ind[0]);
		ret += 2;
	}

	/*
	** get 2nd arg
	*/
	type_arg.adr_reg[3] = *((char*)targ->arg + ret);
	type_arg.val_reg[3] = (targ->bytecode[0] == T_DIR) ?
							type_arg.val_dir[0] :
							type_arg.val_ind[0];
	ret += 1;

	/*
	** process ld
	*/
	put_registry(tproc->registry,				//틀려도 괜찮음.
					type_arg.adr_reg[3],
					&type_arg.val_reg[3]);
	if (type_arg.val_reg[3] == 0)
		tproc->carry = 1;
	t_arg_destroy(targ);
	return (ret + 2);
}

