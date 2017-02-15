/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 22:11:21 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 22:11:22 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		deal_aff(t_arena *tarena, int idx_cham, int idx_proc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	ret = count_bytecode_cycle(tarena->tmap, OP_AFF + 1,
					tarena->tcham[idx_cham]->tproc[idx_proc].pc)
				+ op_tab[OP_AFF].num_bytecode
				+ 1;
	targ = t_arg_new(tarena->tmap,
					tarena->tcham[idx_cham]->tproc[idx_proc].pc,
					OP_AFF + 1);
	if (targ == NULL)
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	if (read_registry(
		tarena->tcham[idx_cham]->tproc[idx_proc].registry,
		((char*)(targ->arg))[0],
		&(type_arg.val_reg[0])))
	{
		#ifdef __DEBUG_JEX
			printf("%s\n", "wrong exit");
		#endif
		t_arg_destroy(targ);
		return (ret);//틀렸을 때 몇 개 반환하는지 보기
	}
	if (tarena->option & NCURSES)
	{
		ncur_show_aff(tarena->twin->win_arena, idx_cham,
						(char)type_arg.val_reg[0]);
	}
	else
	{
		ft_putstr("Aff : ");
		ft_putchar(type_arg.val_reg[0]);
		ft_putstr("\n");
	}
	t_arg_destroy(targ);
	return (ret);
}



// int		deal_aff(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc)
// {
// 	t_arg			*targ;
// 	t_type_arg		type_arg;
// 	int				ret;

// 	ret = count_bytecode_cycle(tmap, OP_AFF + 1, pc_command)
// 				+ op_tab[OP_AFF].num_bytecode
// 				+ 1;
// 	targ = t_arg_new(tmap, pc_command, OP_AFF + 1);
// 	if (targ == NULL)
// 	{
// 		#ifdef __DEBUG_JEX
// 			printf("%s\n", "wrong exit");
// 		#endif
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}
// 	if (read_registry(
// 		tproc->registry,
// 		((char*)(targ->arg))[0],
// 		&(type_arg.val_reg[0])))
// 	{
// 		#ifdef __DEBUG_JEX
// 			printf("%s\n", "wrong exit");
// 		#endif
// 		t_arg_destroy(targ);
// 		return (ret);//틀렸을 때 몇 개 반환하는지 보기
// 	}
// 	ft_putstr("Aff : ");
// 	ft_putchar(type_arg.val_reg[0]);
// 	ft_putstr("\n");
// 	t_arg_destroy(targ);
// 	return (ret);
// }
