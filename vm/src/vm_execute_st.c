/* ************************************************************************** */
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

int		deal_st(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg		*targ;
	TYPE_REG	value_reg;
	TYPE_REG	address_reg;
	TYPE_IND	address_ind;
	TYPE_IND	val_ind;
	int			ret;

	ret = count_bytecode_cycle(tmap, OP_ST + 1, pc_command)
				+ op_tab[OP_ST].num_bytecode
				+ 1;
	targ = t_arg_new(tmap, pc_command, OP_ST + 1);
	if (targ == NULL)
		return (ret);
	if (read_registry(tproc->registry, ((char*)(targ->arg))[0], &value_reg))
	{
		t_arg_destroy(targ);
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	if (targ->bytecode[1] == T_REG)
	{
		if (read_registry(tproc->registry, ((char*)(targ->arg))[1], &address_reg))
		{
			t_arg_destroy(targ);
			return (ret);//틀렸을 때 몇 개 반환하는지 보기
		}
		t_map_put_bytes(tmap,
			pc_command + (address_reg % IDX_MOD),
			&(value_reg), REG_SIZE);
	}
	else // T_IND
	{
		ft_memcpy(&address_ind, ((char*)(targ->arg)) + 1, IND_SIZE);
		ft_endian_convert(&address_ind, 2);
		val_ind = read_indirect_data(tmap, pc_command, address_ind % IDX_MOD);
		t_map_put_bytes(tmap,
			pc_command + (val_ind % IDX_MOD),
			&(value_reg), REG_SIZE);
	}
	t_arg_destroy(targ);
	return (ret);
}
