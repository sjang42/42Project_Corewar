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

	ret = 0;
	opcode = tarena->tcham[idx_cham]->tproc[idx_proc].on_command;
	if (1)
		ncur_erase_termsays(tarena->twin->win_arena);
	if (opcode == op_tab[OP_LIVE].opcode)
	{
		if (1)
			ret += w_deal_live(tarena, tmap, idx_cham, idx_proc);
		// else
		// 	ret += deal_live(tarena, tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
	}
	else if (opcode == op_tab[OP_LD].opcode)
	{
		ret += deal_ld(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_ST].opcode)
	{
		ret += deal_st(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_ADD].opcode)
	{
		ret += deal_add(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_SUB].opcode)
	{
		ret += deal_sub(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
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
		ret += deal_zjmp(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LDI].opcode)
	{
		ret += deal_ldi(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_STI].opcode)
	{
		ret += deal_sti(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc, &(tarena->tcham[idx_cham]->tproc[idx_proc]));
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
		ret += deal_fork(tarena, idx_cham, idx_proc, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
	}
	else if (opcode == op_tab[OP_LFORK].opcode)
	{
		ret += deal_lfork(tmap, tarena->tcham[idx_cham], idx_proc, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
	}
		
	return (ret);
}
