/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_xor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:39:36 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:39:37 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_xor(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				i;
	int				point;
	int				ret;

	ret = count_bytecode_cycle(tmap, OP_XOR + 1, pc_command)
				+ op_tab[OP_XOR].num_bytecode
				+ 1;
	targ = t_arg_new(tmap, pc_command, OP_XOR + 1);
	ft_bzero(&type_arg, sizeof(t_type_arg));
	if (targ == NULL)
	{
		
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	point = 0;
	i = 0;
	/*
	** get 1st, 2nd arg
	*/
	while (i < 2)
	{
		if (targ->bytecode[i] == T_REG)			//get : type_arg.val_reg[i]
		{
			if (read_registry(
				tproc->registry,
				*(((char*)(targ->arg)) + point),
				&(type_arg.val_reg[i])))
			{
				t_arg_destroy(targ);
				return (ret);//틀렸을 때 몇 개 반환하는지 보기
			}
			point += 1;
		}
		else if (targ->bytecode[i] == T_DIR)	//get : type_arg.val_dir[i]
		{
			ft_memcpy(&(type_arg.val_dir[i]),
						(char*)(targ->arg) + point,
						DIR_SIZE);
			ft_endian_convert(&(type_arg.val_dir[i]), DIR_SIZE);
			point += 4;
		}
		else//T_IND								//get : type_arg.val_ind[i]
		{
			ft_memcpy(&(type_arg.adr_ind[i]), (char*)(targ->arg) + point, IND_SIZE);
			ft_endian_convert(&(type_arg.adr_ind[i]), IND_SIZE);
			type_arg.val_ind[i] = (TYPE_IND)read_indirect_data(
								tmap, pc_command,
								type_arg.adr_ind[i] % IDX_MOD);
			point += 2;
		}
		i++;
	}

	/*
	** get 3rd arg
	*/
	type_arg.adr_reg[2] = *(((char*)(targ->arg)) + point);
	point += 1;
	/*
	** process and
	*/
	if (targ->bytecode[0] == T_REG)
	{
		if (targ->bytecode[1] == T_REG)
			type_arg.val_reg[3] = type_arg.val_reg[1] ^ type_arg.val_reg[0];
		else if (targ->bytecode[1] == T_DIR)
			type_arg.val_reg[3] = type_arg.val_dir[1] ^ type_arg.val_reg[0];
		else //targ->bytecode[1] == T_IND
			type_arg.val_reg[3] = type_arg.val_ind[1] ^ type_arg.val_reg[0];
	}
	else if (targ->bytecode[0] == T_DIR)
	{
		if (targ->bytecode[1] == T_REG)
			type_arg.val_reg[3] = type_arg.val_reg[1] ^ type_arg.val_dir[0];
		else if (targ->bytecode[1] == T_DIR)
			type_arg.val_reg[3] = type_arg.val_dir[1] ^ type_arg.val_dir[0];
		else //targ->bytecode[1] == T_IND
			type_arg.val_reg[3] = type_arg.val_ind[1] ^ type_arg.val_dir[0];
	}
	else //((targ->bytecode[0] == T_IND))
	{
		if (targ->bytecode[1] == T_REG)
			type_arg.val_reg[3] = type_arg.val_reg[1] ^ type_arg.val_ind[0];
		else if (targ->bytecode[1] == T_DIR)
			type_arg.val_reg[3] = type_arg.val_dir[1] ^ type_arg.val_ind[0];
		else //targ->bytecode[1] == T_IND
			type_arg.val_reg[3] = type_arg.val_ind[1] ^ type_arg.val_ind[0];
	}
	if (put_registry(tproc->registry,
				type_arg.adr_reg[2],
				&(type_arg.val_reg[3])))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	if (type_arg.val_reg[3] == 0)
		tproc->carry = 1;
	else
		tproc->carry = 0;
	t_arg_destroy(targ);
	return (ret);
}
