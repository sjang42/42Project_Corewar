/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_sti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 17:08:36 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 17:08:38 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

// int		w_deal_sti(t_arena *tarena, int idx_cham, int idx_proc)
// 	// t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg			*targ;
// 	t_type_arg		type_arg;
// 	int				point;
// 	int				ret;
// 	int				where;	

// 	ret = count_bytecode_cycle(tarena->tmap, OP_STI + 1,
// 				tarena->tcham[idx_cham]->tproc[idx_proc].pc)
// 				+ op_tab[OP_STI].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tarena->tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, OP_STI + 1);

// 	/*
// 	**	get 1st arg
// 	*/
// 	if (targ == NULL)
// 		return (ret);
// 	if (read_registry(tarena->tcham[idx_cham]->tproc[idx_proc].registry,
// 		((char*)(targ->arg))[0],
// 		&(type_arg.val_reg[0])))
// 	{
// 		t_arg_destroy(targ);
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}
// 	ft_endian_convert(&(type_arg.val_reg[0]), REG_SIZE);
// 	point = 1;

// 	/*
// 	**	get 2nd arg
// 	*/
// 	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[1]
// 	{
// 		if (read_registry(
// 			tarena->tcham[idx_cham]->tproc[idx_proc].registry,
// 			((char*)(targ->arg))[1],
// 			&(type_arg.val_reg[1])))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 		}
// 		type_arg.adr_reg[1] = ((char*)(targ->arg))[1];
// 		point += 1;
// 	}
// 	else if (targ->bytecode[1] == T_DIR)	//get : type_arg.adr_dir[1]
// 	{
// 		ft_memcpy(&(type_arg.adr_dir[1]),
// 					(char*)(targ->arg) + 1,
// 					DIR_ADR_SIZE);
// 		ft_endian_convert(&(type_arg.adr_dir[1]), DIR_ADR_SIZE);
// 		point += 2;
// 	}
// 	else//T_IND								//get : type_arg.val_ind[1]
// 	{
// 		ft_memcpy(&(type_arg.adr_ind[1]), (char*)(targ->arg) + 1, IND_SIZE);
// 		ft_endian_convert(&(type_arg.adr_ind[1]), IND_SIZE);
// 		type_arg.val_ind[1] = (TYPE_IND)read_indirect_data(
// 							tarena->tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc,
// 							type_arg.adr_ind[1] % IDX_MOD);
// 		point += 2;
// 	}

// 	/*
// 	**	get 3rd arg
// 	*/
// 	if (targ->bytecode[2] == T_REG)			//get : type_arg.val_reg[2]
// 	{
// 		if (read_registry(
// 			tarena->tcham[idx_cham]->tproc[idx_proc].registry,
// 			((char*)(targ->arg))[2],
// 			&(type_arg.val_reg[2])))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 		}
// 		point += 1;
// 	}
// 	else						//T_DIR		//get : type_arg.adr_dir[2]
// 	{
// 		ft_memcpy(&(type_arg.adr_dir[2]),
// 					(char*)(targ->arg) + point,
// 					DIR_ADR_SIZE);
// 		ft_endian_convert(&(type_arg.adr_dir[2]), DIR_ADR_SIZE);
// 		point += 2;
// 	}

// 	/*
// 	**	process sti
// 	*/
// 	if (targ->bytecode[2] == T_REG)
// 	{
// 		if (targ->bytecode[1] == T_REG)
// 			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.val_reg[2];
// 		else if (targ->bytecode[1] == T_DIR)
// 			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.val_reg[2];
// 		else //targ->bytecode[1] == T_IND
// 			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.val_reg[2];
// 	}
// 	else //T_DIR
// 	{
// 		if (targ->bytecode[1] == T_REG)
// 			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.adr_dir[2];
// 		else if (targ->bytecode[1] == T_DIR)
// 			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.adr_dir[2];
// 		else //targ->bytecode[1] == T_IND
// 			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.adr_dir[2];
// 	}
// 	// w_t_map_put_bytes(tarena->tmap,
// 	// 		tarena->tcham[idx_cham]->tproc[idx_proc].pc + (type_arg.val_dir[3] % IDX_MOD),
// 	// 		&(type_arg.val_reg[0]),
// 	// 		REG_SIZE);

// 	//
// 	where = tarena->tcham[idx_cham]->tproc[idx_proc].pc +
// 			(type_arg.val_dir[3] % IDX_MOD);
// 	w_sti_reg_to_map(tarena, idx_cham, where, &(type_arg.val_reg[0]));
// 	if (tarena->option & NCURSES)
// 		ncur_map_update(tarena, where, REG_SIZE);
// 	//
// 	t_arg_destroy(targ);
// 	return (ret);
// }



// int		deal_sti(t_map *tmap, int pc_command, t_proc *tproc)
int		deal_sti(t_arena *tarena, int idx_cham, int idx_proc)

{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				point;
	int				ret;
	int 			pc_command;
	t_proc			*tproc;
	int 			where;

	pc_command = tarena->tcham[idx_cham]->tproc[idx_proc].pc;
	tproc = &(tarena->tcham[idx_cham]->tproc[idx_proc]);

	ret = count_bytecode_cycle(tarena->tmap, OP_STI + 1, pc_command)
				+ op_tab[OP_STI].num_bytecode + 1;
	targ = t_arg_new(tarena->tmap, pc_command, OP_STI + 1);
	/*
	**	get 1st arg
	*/
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);
	}
	if (read_registry(tproc->registry,
		((char*)(targ->arg))[0],
		&(type_arg.val_reg[0])))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	point = 1;
	
	#ifdef __DEBUG_JEX
		printf("%s\n", "hi2");
	#endif
	/*
	**	get 2nd arg
	*/
	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[1]
	{
		if (read_registry(
			tproc->registry,
			((char*)(targ->arg))[1],
			&(type_arg.val_reg[1])))
		{
			t_arg_destroy(targ);
			return (ret);//틀렸을 때 몇 개 반환하는지 보기
		}
		type_arg.adr_reg[1] = ((char*)(targ->arg))[1];
		point += 1;
	}
	else if (targ->bytecode[1] == T_DIR)	//get : type_arg.adr_dir[1]
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "dir");
		#endif
		ft_memcpy(&(type_arg.adr_dir[1]),
					(char*)(targ->arg) + 1,
					DIR_ADR_SIZE);
		ft_endian_convert(&(type_arg.adr_dir[1]), DIR_ADR_SIZE);
		point += 2;
	}
	else//T_IND								//get : type_arg.val_ind[1]
	{
		ft_memcpy(&(type_arg.adr_ind[1]), (char*)(targ->arg) + 1, IND_SIZE);
		ft_endian_convert(&(type_arg.adr_ind[1]), IND_SIZE);
		type_arg.val_ind[1] = (TYPE_IND)read_indirect_data(
							tarena->tmap, pc_command,
							type_arg.adr_ind[1] % IDX_MOD);
		point += 2;
	}

	/*
	**	get 3rd arg
	*/
	if (targ->bytecode[2] == T_REG)			//get : type_arg.val_reg[2]
	{
		if (read_registry(
			tproc->registry,
			*(((char*)(targ->arg)) + point),
			&(type_arg.val_reg[2])))
		{
			#ifdef __DEBUG_JEX
				printf("idx : %d\n", *(((char*)(targ->arg)) + point));
				printf("%s\n", "hi1");
			#endif
			t_arg_destroy(targ);
			return (ret);//틀렸을 때 몇 개 반환하는지 보기
		}
		point += 1;
	}
	else						//T_DIR		//get : type_arg.adr_dir[2]
	{
		ft_memcpy(&(type_arg.adr_dir[2]),
					(char*)(targ->arg) + point,
					DIR_ADR_SIZE);
		ft_endian_convert(&(type_arg.adr_dir[2]), DIR_ADR_SIZE);
		point += 2;
	}

	/*
	**	process sti
	*/
	if (targ->bytecode[2] == T_REG)
	{
		if (targ->bytecode[1] == T_REG)
			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.val_reg[2];
		else if (targ->bytecode[1] == T_DIR)
			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.val_reg[2];
		else //targ->bytecode[1] == T_IND
			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.val_reg[2];
	}
	else //T_DIR
	{
		if (targ->bytecode[1] == T_REG)
			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.adr_dir[2];
		else if (targ->bytecode[1] == T_DIR)
			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.adr_dir[2];
		else //targ->bytecode[1] == T_IND
			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.adr_dir[2];
	}

	where = pc_command + (type_arg.val_dir[3] % IDX_MOD);
	if (where < 0)
		where += (MEM_SIZE);

	#ifdef __DEBUG_JEX
		printf("%s\n", "hi");
		if (tarena->cycle > 4820)
		{
			printf("where : %d\n", where);
			printf("pc_command : %d\n", pc_command);
			printf("type_arg.val_dir[3] : %d\n", type_arg.val_dir[3]);
			printf("IDX_MOD : %d\n", IDX_MOD);
			printf("type_arg.val_reg[0] : %d\n", type_arg.val_reg[0]);
		}
	#endif

	w_sti_reg_to_map(tarena, idx_cham, where, &(type_arg.val_reg[0]));
	if (tarena->option & NCURSES)
		ncur_map_update(tarena, where, REG_SIZE);
	//
	// t_map_put_bytes(tarena->tmap,
	// 		pc_command + (type_arg.val_dir[3] % IDX_MOD),
	// 		&(type_arg.val_reg[0]),
	// 		REG_SIZE);
	// if (tarena->option & COMMANDS)
	// {
		
	// }
	if (tarena->option & COMMANDS)
		show_commands_sti(targ, type_arg, tproc, where);
	t_arg_destroy(targ);
	return (ret);
}






// int		deal_sti(t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg			*targ;
// 	t_type_arg		type_arg;
// 	int				point;
// 	int				ret;

// 	ret = count_bytecode_cycle(tmap, OP_STI + 1, pc_command)
// 				+ op_tab[OP_STI].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_STI + 1);

// 	/*
// 	**	get 1st arg
// 	*/
// 	if (targ == NULL)
// 		return (ret);
// 	if (read_registry(tproc->registry,
// 		((char*)(targ->arg))[0],
// 		&(type_arg.val_reg[0])))
// 	{
// 		t_arg_destroy(targ);
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}
// 	ft_endian_convert(&(type_arg.val_reg[0]), REG_SIZE);
// 	point = 1;

// 	/*
// 	**	get 2nd arg
// 	*/
// 	if (targ->bytecode[1] == T_REG)			//get : type_arg.val_reg[1]
// 	{
// 		if (read_registry(
// 			tproc->registry,
// 			((char*)(targ->arg))[1],
// 			&(type_arg.val_reg[1])))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 		}
// 		type_arg.adr_reg[1] = ((char*)(targ->arg))[1];
// 		point += 1;
// 	}
// 	else if (targ->bytecode[1] == T_DIR)	//get : type_arg.adr_dir[1]
// 	{
// 		ft_memcpy(&(type_arg.adr_dir[1]),
// 					(char*)(targ->arg) + 1,
// 					DIR_ADR_SIZE);
// 		ft_endian_convert(&(type_arg.adr_dir[1]), DIR_ADR_SIZE);
// 		point += 2;
// 	}
// 	else//T_IND								//get : type_arg.val_ind[1]
// 	{
// 		ft_memcpy(&(type_arg.adr_ind[1]), (char*)(targ->arg) + 1, IND_SIZE);
// 		ft_endian_convert(&(type_arg.adr_ind[1]), IND_SIZE);
// 		type_arg.val_ind[1] = (TYPE_IND)read_indirect_data(
// 							tmap, pc_command,
// 							type_arg.adr_ind[1] % IDX_MOD);
// 		point += 2;
// 	}

// 	/*
// 	**	get 3rd arg
// 	*/
// 	if (targ->bytecode[2] == T_REG)			//get : type_arg.val_reg[2]
// 	{
// 		if (read_registry(
// 			tproc->registry,
// 			((char*)(targ->arg))[2],
// 			&(type_arg.val_reg[2])))
// 		{
// 			t_arg_destroy(targ);
// 			return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 		}
// 		point += 1;
// 	}
// 	else						//T_DIR		//get : type_arg.adr_dir[2]
// 	{
// 		ft_memcpy(&(type_arg.adr_dir[2]),
// 					(char*)(targ->arg) + point,
// 					DIR_ADR_SIZE);
// 		ft_endian_convert(&(type_arg.adr_dir[2]), DIR_ADR_SIZE);
// 		point += 2;
// 	}

// 	/*
// 	**	process sti
// 	*/
// 	if (targ->bytecode[2] == T_REG)
// 	{
// 		if (targ->bytecode[1] == T_REG)
// 			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.val_reg[2];
// 		else if (targ->bytecode[1] == T_DIR)
// 			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.val_reg[2];
// 		else //targ->bytecode[1] == T_IND
// 			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.val_reg[2];
// 	}
// 	else //T_DIR
// 	{
// 		if (targ->bytecode[1] == T_REG)
// 			type_arg.val_dir[3] = type_arg.val_reg[1] + type_arg.adr_dir[2];
// 		else if (targ->bytecode[1] == T_DIR)
// 			type_arg.val_dir[3] = type_arg.adr_dir[1] + type_arg.adr_dir[2];
// 		else //targ->bytecode[1] == T_IND
// 			type_arg.val_dir[3] = type_arg.val_ind[1] + type_arg.adr_dir[2];
// 	}

// 	t_map_put_bytes(tmap,
// 			pc_command + (type_arg.val_dir[3] % IDX_MOD),
// 			&(type_arg.val_reg[0]),
// 			REG_SIZE);




// 	t_arg_destroy(targ);
// 	return (ret);
// }

