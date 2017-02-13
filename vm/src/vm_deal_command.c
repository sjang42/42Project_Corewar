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

int		deal_command(t_map *tmap, int idx_cham,
					int idx_proc, t_arena *tarena)
{
	int ret;
	int opcode;

	//debug
	//
	#ifdef __DEBUG_JEX
		if (tarena->cycle > 4380)
		{
			int mem;
			int test = 0x000000ff;
			printf("\n%s\n", "here is me!!");
			printf("idx_cham : %x\n", idx_cham);
			printf("idx_proc : %x\n", idx_proc);
			printf("op : %d\n", tarena->tcham[idx_cham]->tproc[idx_proc].on_command);
			printf("pc : %x\n", tarena->tcham[idx_cham]->tproc[idx_proc].pc);
			printf("carry : %x\n", tarena->tcham[idx_cham]->tproc[idx_proc].carry);
			printf("cycle : %d\n", tarena->cycle);
			ft_print_memory(tarena->tcham[idx_cham]->tproc[idx_proc].registry[4], REG_SIZE);

			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[0], 4);
			printf("r1 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[1], 4);
			printf("r2 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[2], 4);
			printf("r3 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[3], 4);
			printf("r4 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[4], 4);
			printf("r5 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[5], 4);
			printf("r6 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[6], 4);
			printf("r7 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[7], 4);
			printf("r8 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[8], 4);
			printf("r9 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[9], 4);
			printf("r10 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[12], 4);
			printf("r13 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[13], 4);
			printf("r14 : %d\n", mem);
			ft_memcpy(&mem, tarena->tcham[idx_cham]->tproc[idx_proc].registry[14], 4);
			printf("r15 : %d\n", mem);

			// printf("test : %d\n", test);
			printf("%s\n", "");
		}
	#endif
	// 
	//debug

	ret = 0;
	opcode = tarena->tcham[idx_cham]->tproc[idx_proc].on_command;
	if (opcode == op_tab[OP_LIVE].opcode)
	{
		// if (tarena->option & NCURSES)
		// 	ret += w_deal_live(tarena, tmap, idx_cham, idx_proc);
		// else
			ret += deal_live(tarena, tmap, idx_cham, idx_proc);
	}
	else if (opcode == op_tab[OP_LD].opcode)
	{
		ret += deal_ld(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_ST].opcode)
	{
		ret += w_deal_st(tarena, idx_cham, idx_proc);
		// ret += deal_st(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_ADD].opcode)
	{
		ret += deal_add(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_SUB].opcode)
	{
		ret += deal_sub(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_AND].opcode)
	{
		ret += deal_and(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_OR].opcode)
	{
		ret += deal_or(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_XOR].opcode)
	{
		ret += deal_xor(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_ZJMP].opcode)
	{
		ret += deal_zjmp(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LDI].opcode)
	{
		ret += deal_ldi(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_STI].opcode)
	{
		// if (tarena->option & NCURSES)
		// 	ret += w_deal_sti(tarena, idx_cham, idx_proc);
		// else
			ret += deal_sti(tarena, idx_cham, idx_proc);
			// ret += deal_sti(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LLD].opcode)
	{
		ret += deal_lld(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LLDI].opcode)
	{
		ret += deal_lldi(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_AFF].opcode)
	{
		ret += deal_aff(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_FORK].opcode)
	{
		ret += w_deal_fork(tarena, idx_cham, idx_proc, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
	}
	else if (opcode == op_tab[OP_LFORK].opcode)
	{
		ret += w_deal_lfork(tarena, idx_cham, idx_proc, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
	}
		
	return (ret);
}
