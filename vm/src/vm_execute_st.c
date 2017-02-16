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

int		w_deal_st(t_arena *tarena, int idx_cham, int idx_proc)
{
	t_arg		*targ;
	t_type_arg	type_arg;
	int			where;

	TYPE_REG	value_reg;
	TYPE_REG	address_reg;
	TYPE_IND	address_ind;
	TYPE_IND	val_ind;
	int			ret;

	//debug
		// printf("st pc : %x\n", tarena->tcham[idx_cham]->tproc[idx_proc].pc);
		// printf("cycle : %d\n", tarena->cycle);
	//debug
	ft_bzero(&type_arg, sizeof(t_type_arg));
	ret = count_bytecode_cycle(tarena->tmap, OP_ST + 1,
			tarena->tcham[idx_cham]->tproc[idx_proc].pc)
				+ op_tab[OP_ST].num_bytecode
				+ 1;
	targ = t_arg_new(tarena->tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, OP_ST + 1);
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);
	}

	/*
	** get 1st arg : type_arg.val_reg[0]
	*/
	if (read_registry(tarena->tcham[idx_cham]->tproc[idx_proc].registry,
		((char*)(targ->arg))[0],
		&(type_arg.val_reg[0])))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);
	}

	/*
	** get 2nd arg and process st
	*/
	if (targ->bytecode[1] == T_REG)
	{
		type_arg.adr_reg[1] = ((char*)(targ->arg))[1];
		if (put_registry(tarena->tcham[idx_cham]->tproc[idx_proc].registry,
			type_arg.adr_reg[1], &(type_arg.val_reg[0])))
		{
			t_arg_destroy(targ);
			return (ret);
		}

	}
	else //(targ->bytecode[1] == T_IND)
	{
		ft_memcpy(&(type_arg.adr_ind[1]), (char*)(targ->arg) + 1, IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[1]), IND_SIZE);
		where = tarena->tcham[idx_cham]->tproc[idx_proc].pc +
				(type_arg.adr_ind[1] % IDX_MOD);
		#ifdef __DEBUG_JEX
			if (tarena->cycle > 4380)
			{
				printf("((char*)(targ->arg))[0] : %d\n", ((char*)(targ->arg))[0]);
				printf("type_arg.val_reg[0] : %d\n", type_arg.val_reg[0]);
			}
		#endif
		w_sti_reg_to_map(tarena, idx_cham, where, &(type_arg.val_reg[0]));
		if (tarena->option & NCURSES)
			ncur_map_update(tarena, where, REG_SIZE);
	}
	if (tarena->option & COMMANDS)
		show_commands_st(&(tarena->tcham[idx_cham]->tproc[idx_proc]), targ, type_arg.adr_ind[1]);
	
	//debug
		// if (tarena->tcham[idx_cham]->tproc[idx_proc].number + 1 == 2880)
		// {
		// 	printf("p num : %d\n", tarena->tcham[idx_cham]->tproc[idx_proc].number + 1);
		// 	printf("pc_command : %x\n", tarena->tcham[idx_cham]->tproc[idx_proc].pc);			
		// 	if (targ->bytecode[1] == T_REG)
		// 		printf("bytecode[1] == T_REG\n");
		// 	else if (targ->bytecode[1] == T_IND)
		// 		printf("bytecode[1] == T_IND\n");
		// 	else if (targ->bytecode[1] == T_DIR)
		// 		printf("bytecode[1] == T_DIR\n");
		// 	else
		// 		printf("bytecode[1] : %d\n", targ->bytecode[1]);
		// 	printf("It is r%d\n", type_arg.adr_reg[1]);
		// }
	//debug


	t_arg_destroy(targ);
	return (ret);
}

// int		deal_st(t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg		*targ;
// 	TYPE_REG	value_reg;
// 	TYPE_REG	address_reg;
// 	TYPE_IND	address_ind;
// 	TYPE_IND	val_ind;
// 	int			ret;

// 	ret = count_bytecode_cycle(tmap, OP_ST + 1, pc_command)
// 				+ op_tab[OP_ST].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_ST + 1);
// 	if (targ == NULL)
// 		return (ret);
// 	/*
// 	** get 1st arg : value_reg
// 	*/
// 	if (read_registry(tproc->registry, ((char*)(targ->arg))[0], &value_reg))
// 	{
// 		t_arg_destroy(targ);
// 		return (ret);
// 	}
// 	/*
// 	** get 2nd arg and process st
// 	*/
// 	if (targ->bytecode[1] == T_REG)
// 	{
// 		if (read_registry(tproc->registry, ((char*)(targ->arg))[1], &address_reg))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);
// 		}
// 		put_registry(tproc->registry, address_reg, &value_reg);
// 	}
// 	else //(targ->bytecode[1] == T_IND)
// 	{
// 		ft_memcpy(&address_ind, ((char*)(targ->arg)) + 1, IND_SIZE);
// 		ft_endian_convert(&address_ind, 2);
// 		// val_ind = read_indirect_data(tmap, pc_command, address_ind % IDX_MOD);
// 		t_map_put_bytes(tmap, pc_command + (address_ind % IDX_MOD),
// 						&(value_reg),
// 						REG_SIZE);
// 	}
// 	t_arg_destroy(targ);
// 	return (ret);
// }



// int		deal_st(t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg		*targ;
// 	TYPE_REG	value_reg;
// 	TYPE_REG	address_reg;
// 	TYPE_IND	address_ind;
// 	TYPE_IND	val_ind;
// 	int			ret;

// 	ret = count_bytecode_cycle(tmap, OP_ST + 1, pc_command)
// 				+ op_tab[OP_ST].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_ST + 1);
// 	if (targ == NULL)
// 		return (ret);
// 	if (read_registry(tproc->registry, ((char*)(targ->arg))[0], &value_reg))
// 	{
// 		t_arg_destroy(targ);
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}
// 	if (targ->bytecode[1] == T_REG)
// 	{
// 		if (read_registry(tproc->registry, ((char*)(targ->arg))[1], &address_reg))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 		}
// 		t_map_put_bytes(tmap,
// 			pc_command + (address_reg % IDX_MOD),
// 			&(value_reg), REG_SIZE);
// 	}
// 	else // T_IND
// 	{
// 		ft_memcpy(&address_ind, ((char*)(targ->arg)) + 1, IND_SIZE);
// 		ft_endian_convert(&address_ind, 2);
// 		val_ind = read_indirect_data(tmap, pc_command, address_ind % IDX_MOD);
// 		t_map_put_bytes(tmap,
// 			pc_command + (val_ind % IDX_MOD),
// 			&(value_reg), REG_SIZE);
// 	}
// 	t_arg_destroy(targ);
// 	return (ret);
// }
