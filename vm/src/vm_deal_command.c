/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_deal_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:29:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 18:29:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_live(t_map *tmap, int pc_command)
{
	t_arg	*targ;
	int		num;
	int		i;

	i = 0;
	targ = t_arg_new(tmap, pc_command, OP_LIVE + 1);
	if (targ == NULL)
		return (5);//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
	ft_memcpy(&num, targ->arg, 4);
	ft_endian_convert(&num, 4);
	if (num < 0)//live 넘버가 터무니없는 경우 지나가기만 하고 실행 하진 않음
		return (5);
	ft_putstr("“A process shows that player ");
	ft_putnbr(num);
	ft_putstr(" is alive”\n");
	t_arg_destroy(targ);
	return (5);
}

int		deal_ld(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg	*targ;
	int		num;
	short	idx_ind;
	int		idx_reg;
	int		ret;
	char mem[2];

	targ = t_arg_new(tmap, pc_command, OP_LD + 1);
	idx_ind = 0;
	if (targ == NULL)
		return (5);//틀렸을 때 몇 개 반환하는지 보기
	if (targ->bytecode[0] == T_DIR)
	{
		ret = 4;
		ft_memcpy(&num, targ->arg, 4);
		ft_endian_convert(&num, 4);
	}
	else						//T_IND
	{
		ret = 2;
		ft_memcpy(&idx_ind, targ->arg, 2);
		ft_endian_convert(&idx_ind, 2);
		num = (int)read_indirect_data(tmap, pc_command, idx_ind);
	}
	idx_reg = *((char*)targ->arg + ret);
	put_registry(tproc->registry, idx_reg, &num);
	ret += 1;
	t_arg_destroy(targ);
	return (ret + 2);
}

int		check_registry_idx(int idx)
{
	if (idx < 1 || idx > REG_NUMBER)
		return (-1);
	return (0);
}

int		deal_st(t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg		*targ;
	TYPE_REG	value_reg;
	TYPE_REG	address_reg;
	TYPE_IND	address_ind;
	TYPE_IND	val_ind;
	int			ret;

	ret = 1;
	targ = t_arg_new(tmap, pc_command, OP_ST + 1);
	if (targ == NULL ||
		read_registry(tproc->registry, ((char*)(targ->arg))[0], &value_reg))
	{
		t_arg_destroy(targ);
		return (5);//틀렸을 때 몇 개 반환하는지 보기
	}
	if (targ->bytecode[0] == T_REG)
	{
		if (read_registry(tproc->registry, ((char*)(targ->arg))[1], &address_reg))
		{
			t_arg_destroy(targ);
			return (5);//틀렸을 때 몇 개 반환하는지 보기
		}
		t_map_put_bytes(tmap,
			pc_command + (address_reg % IDX_MOD),
			&(value_reg), REG_SIZE);
		ret += 1;
	}
	else // T_IND
	{
		ft_memcpy(&address_ind, (char*)(targ->arg) + 1, IND_SIZE);
		val_ind = read_indirect_data(tmap, pc_command, address_ind);
		t_map_put_bytes(tmap,
			pc_command + (val_ind % IDX_MOD),
			&(value_reg), REG_SIZE);
		ret += 2;
	}
	t_arg_destroy(targ);
	return (ret + 2);
}

int		deal_command(t_map *tmap, t_proc *tproc,
					int opcode, int pc_command)
{
	int ret;

	ret = 0;
	if (opcode == op_tab[OP_LIVE].opcode)
		ret += deal_live(tmap, pc_command);
	else if (opcode == op_tab[OP_LD].opcode)
		ret += deal_ld(tmap, pc_command, tproc);
	else if (opcode == op_tab[OP_LD].opcode)
		ret += deal_st(tmap, pc_command, tproc);
	return (ret);
}
