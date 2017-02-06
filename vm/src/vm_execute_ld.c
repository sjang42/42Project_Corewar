/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_ld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:12:55 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:12:57 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_ld(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ft_bzero(&type_arg, sizeof(t_type_arg));
	targ = t_arg_new(tmap, pc_command, OP_LD + 1);
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
	else						//TYPE_IND		//get : type_arg.val_ind[0]
	{
		ft_memcpy(&(type_arg.adr_ind[0]), (char*)(targ->arg), IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[0]), IND_SIZE);
		type_arg.val_ind[0] = (TYPE_IND)read_indirect_data(
							tmap, pc_command,
							type_arg.adr_ind[0] % IDX_MOD);
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


// int		deal_ld(t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg	*targ;
// 	int		num;
// 	short	idx_ind;
// 	int		idx_reg;
// 	int		ret;
// 	char mem[2];

// 	targ = t_arg_new(tmap, pc_command, OP_LD + 1);
// 	idx_ind = 0;
// 	if (targ == NULL)
// 		return (5);//틀렸을 때 몇 개 반환하는지 보기
// 	if (targ->bytecode[0] == T_DIR)
// 	{
// 		ret = 4;
// 		ft_memcpy(&num, targ->arg, 4);
// 		ft_endian_convert(&num, 4);
// 	}
// 	else						//T_IND
// 	{
// 		ret = 2;
// 		ft_memcpy(&idx_ind, targ->arg, 2);
// 		ft_endian_convert(&idx_ind, 2);
// 		num = (int)read_indirect_data(tmap,
// 			pc_command,
// 			idx_ind % IDX_MOD);
// 	}
// 	idx_reg = *((char*)targ->arg + ret);
// 	put_registry(tproc->registry, idx_reg, &num);
// 	ret += 1;
// 	t_arg_destroy(targ);
// 	return (ret + 2);
// }
