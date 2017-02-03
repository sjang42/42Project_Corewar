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
	unsigned 	tmp[4];
	int			num;
	int 		i;

	i = 0;
	while (i < 4)
	{
		tmp[i] = get_current_byte(tmap, pc_command + 1 + i);
		i++;
	}
	ft_memcpy(&num, tmp, 4);
	ft_putstr("“A process shows that player ");
	ft_putnbr(num);
	ft_putstr(" is alive”\n");
	return (4);
}

int		deal_ld(t_map *tmap, int pc_command, t_proc *tproc)
{
	char			*tmp;
	int				arg[2];
	int				*arg_byte;
	int				ret;

	ft_bzero(arg, sizeof(int) * 2);
	arg_byte = get_bytecode(tmap, pc_command, op_tab[OP_LD].num_arg);
	if (check_arg_byte(arg_byte))
		return (0);// 바이트코드가 틀릴 때 몇 개를 건너 뛰는지 알아보기
	ret = 4;
	if (arg_byte[0] == T_DIR)
		ret = 4;
	else if (arg_byte[0] == T_IND)
		ret = 2;
	else
		ret = 2;// 바이트코드가 틀릴 때 몇 개를 건너 뛰는지 알아보기
	if (arg_byte[0] == T_DIR || arg_byte[0] == T_IND)
	{
		tmp = (char*)get_data(tmap, pc_command + 2, ret);
		ft_memcpy(&(arg[0]), tmp, ret);
		free(tmp);
	}
	else
	{
		free(arg_byte);
	}

	if (arg_byte[0] == T_IND)
	{
		arg[0] = get_indirect_data(tmap, pc_command, arg[0]);
	}
	if (arg_byte[1] == T_REG)
	{
		tmp = (char*)get_data(tmap, pc_command + ret, 1);
		ft_memcpy(&(arg[1]), tmp, 1);
		if (arg[1] >= 1 && arg[1] <= REG_NUMBER)
			ft_memcpy(tproc->registry[arg[1] - 1], arg[0], REG_SIZE);
		ret += 1;
	}
	free(arg_byte);
	free(tmp);
	return (ret);
}

int		deal_st(t_map *tmap, int pc_command, t_proc *tproc)
{
	char			*tmp;
	int				*arg_byte;
	int				arg[2];
	int				ret;

	ft_bzero(arg, sizeof(int) * 2);
	arg_byte = get_bytecode(tmap, pc_command + 1, op_tab[OP_ST].num_arg)
	if (check_arg_byte(arg_byte))
		return (0);// 바이트코드가 틀릴 때 몇 개를 건너 뛰는지 알아보기
	arg[0] = get_current_byte(tmap, pc_command + 2);
	ret = 1;
	if (arg_byte[1] == T_REG)
		ret += 1;
	else if (arg_byte[1] == T_IND)
		ret += 2;
	tmp = (char*)get_data(tmap, pc_command + 3, ret - 1);
	ft_memcpy(&(arg[1]), tmp, ret - 1);
}

int deal_command(int opcode, t_map *tmap, t_champion *tcham)
{
	int ret;

	ret = 0;
	if (opcode == op_tab[OP_LIVE].opcode)
		ret += deal_live(tmap, tcham->tproc.pc)
	else if (opcode == op_tab[OP_LD].opcode)
		ret += deal_ld(tmap, tcham->tproc.pc)
	return (ret);
}
