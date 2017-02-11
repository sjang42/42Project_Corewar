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
	int				point;

	ret = count_bytecode_cycle(tmap, OP_LLD + 1, pc_command)
				+ op_tab[OP_LLD].num_bytecode
				+ 1;
	ft_bzero(&type_arg, sizeof(t_type_arg));
	targ = t_arg_new(tmap, pc_command, OP_LLD + 1);
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	point = 0;

	/*
	** get 1st arg
	*/
	if (targ->bytecode[0] == T_DIR)				//get : type_arg.val_dir[0]
	{
		ft_memcpy(&(type_arg.val_dir[0]),
					(char*)(targ->arg),
					DIR_SIZE);
		ft_endian_convert(&(type_arg.val_dir[0]), DIR_SIZE);
		point += 4;
	}
	else//(targ->bytecode[0] == T_IND)			//get : type_arg.val_ind[0]
	{
		ft_memcpy(&(type_arg.adr_ind[0]), (char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[0]), IND_SIZE);
		type_arg.val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg.adr_ind[0]);
		point += 2;
	}

	/*
	** get 2nd arg
	*/
	type_arg.adr_reg[3] = *((char*)targ->arg + point);
	type_arg.val_reg[3] = (targ->bytecode[0] == T_DIR) ?
							type_arg.val_dir[0] :
							type_arg.val_ind[0];
	point += 1;

	/*
	** process ld
	*/
	if (put_registry(tproc->registry,
					type_arg.adr_reg[3],
					&type_arg.val_reg[3]))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);
	}
	if (type_arg.val_reg[3] == 0)
		tproc->carry = 1;
	else
		tproc->carry = 1;
	t_arg_destroy(targ);
	return (ret);
}

