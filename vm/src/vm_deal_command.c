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

int		deal_command(t_map *tmap, int opcode, t_champion *tcham, int idx_proc)
{
	int ret;

	ret = 0;
	if (opcode == op_tab[OP_LIVE].opcode)
	{
		ret += deal_live(tmap, tcham->tproc[idx_proc].pc);
	}
	else if (opcode == op_tab[OP_LD].opcode)
	{
		ret += deal_ld(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_ST].opcode)
	{
		ret += deal_st(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_ADD].opcode)
	{
		ret += deal_add(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}

	else if (opcode == op_tab[OP_SUB].opcode)
	{
		ret += deal_sub(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_AND].opcode)
	{
		ret += deal_and(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_OR].opcode)
	{
		ret += deal_or(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_XOR].opcode)
	{
		ret += deal_xor(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_ZJMP].opcode)
	{
		ret += deal_zjmp(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LDI].opcode)
	{
		ret += deal_ldi(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_STI].opcode)
	{
		ret += deal_sti(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LLD].opcode)
	{
		ret += deal_lld(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_LLDI].opcode)
	{
		ret += deal_lldi(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_AFF].opcode)
	{
		ret += deal_aff(tmap, tcham->tproc[idx_proc].pc, &(tcham->tproc[idx_proc]));
	}
	else if (opcode == op_tab[OP_FORK].opcode)
	{
		ret += deal_fork(tmap, tcham, idx_proc, tcham->tproc[idx_proc].pc);
	}
	else if (opcode == op_tab[OP_LFORK].opcode)
	{
		ret += deal_lfork(tmap, tcham, idx_proc, tcham->tproc[idx_proc].pc);
	}
	return (ret);
}
