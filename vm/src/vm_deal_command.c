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

static int		deal_command_sub(t_arena *tarena, t_map *tmap,
									int idx_cham, int idx_proc)
{
	int 	opcode;
	int 	pc_command;
	t_proc	*tproc;

	opcode = tarena->tcham[idx_cham]->tproc[idx_proc].on_command;
	pc_command = tarena->tcham[idx_cham]->tproc[idx_proc].pc;
	tproc = &(tarena->tcham[idx_cham]->tproc[idx_proc]);
	if (opcode == op_tab[OP_ZJMP].opcode)
		return (deal_zjmp(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_LDI].opcode)
		return (deal_ldi(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_STI].opcode)
		return (deal_sti(tarena, tmap, idx_cham, idx_proc));
	else if (opcode == op_tab[OP_LLD].opcode)
		return (deal_lld(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_LLDI].opcode)
		return (deal_lldi(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_AFF].opcode)
		return (deal_aff(tarena, idx_cham, idx_proc));
	else if (opcode == op_tab[OP_FORK].opcode)
		return (deal_fork(tarena, idx_cham, idx_proc, pc_command));
	else if (opcode == op_tab[OP_LFORK].opcode)
		return (deal_lfork(tarena, idx_cham, idx_proc, pc_command));
	return (0);
}

int				deal_command(t_map *tmap, int idx_cham,
								int idx_proc, t_arena *tarena)
{
	int opcode;
	int pc_command;
	t_proc *tproc;

	opcode = tarena->tcham[idx_cham]->tproc[idx_proc].on_command;
	pc_command = tarena->tcham[idx_cham]->tproc[idx_proc].pc;
	tproc = &(tarena->tcham[idx_cham]->tproc[idx_proc]);
	if (opcode == op_tab[OP_LIVE].opcode)
		return (deal_live(tarena, tmap, idx_cham, idx_proc));
	else if (opcode == op_tab[OP_LD].opcode)
		return (deal_ld(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_ST].opcode)
		return (deal_st(tarena, tmap, idx_cham, idx_proc));
	else if (opcode == op_tab[OP_ADD].opcode)
		return (deal_add(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_SUB].opcode)
		return (deal_sub(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_AND].opcode)
		return (deal_and(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_OR].opcode)
		return (deal_or(tarena, tmap, pc_command, tproc));
	else if (opcode == op_tab[OP_XOR].opcode)
		return (deal_xor(tarena, tmap, pc_command, tproc));
	else
		return (deal_command_sub(tarena, tmap, idx_cham, idx_proc));
}
