/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:12:44 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 18:12:46 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		is_opcode(char byte)
{
	if (byte >= MIN_OPCODE && byte <= MAX_OPCODE)
		return (1);
	else
		return (0);
}

int		get_cycle(int opcode)
{
	return (op_tab[opcode - 1].num_cycle);
}

int		vm_execute_proc(t_map *tmap, int idx_cham, t_arena *tarena,
						int idx_proc)
{
	int cur_byte;
	int ret;

	if (!(tarena->tcham[idx_cham]->tproc[idx_proc].on_command))
	{
	

		cur_byte = read_current_byte(tmap, tarena->tcham[idx_cham]->tproc[idx_proc].pc);
		if (is_opcode(cur_byte))
		{
			#ifdef __DEBUG_JEX
				if (tarena->cycle > 4380)
				{
					printf("came in cycle for %d : %d\n",
							cur_byte,
							tarena->cycle);
				}
			#endif
			tarena->tcham[idx_cham]->tproc[idx_proc].on_command = cur_byte;
			tarena->tcham[idx_cham]->tproc[idx_proc].wait_cycle = get_cycle(cur_byte) - 1;
			return (0);
		}
		else
		{
	#ifdef __DEBUG_JEX
			printf("%s\n", "do i come");
	#endif
			return (1);
		}
	}
	else
	{
		if (tarena->tcham[idx_cham]->tproc[idx_proc].wait_cycle == 1)
		{
	#ifdef __DEBUG_JEX
			if (tarena->cycle > 4380)
		{
			printf("executing cycle for %d : %d\n\n",
					tarena->tcham[idx_cham]->tproc[idx_proc].on_command,
					tarena->cycle);
		}
	#endif
			ret = deal_command(tmap, idx_cham, idx_proc, tarena);
			tarena->tcham[idx_cham]->tproc[idx_proc].on_command = 0;
			return (ret);
		}
		else
		{
			(tarena->tcham[idx_cham]->tproc[idx_proc].wait_cycle) -= 1;
			return (0);
		}
	}
}


// int		vm_execute_proc(t_map *tmap, t_champion *tcham,
// 						int idx_cham, int idx_proc)
// {
// 	int cur_byte;
// 	int ret;

// 	if (!(tproc->on_command))
// 	{
// 		cur_byte = read_current_byte(tmap, tproc->pc);
// 		if (is_opcode(cur_byte))
// 		{
// 			tproc->on_command = cur_byte;
// 			tproc->wait_cycle = get_cycle(cur_byte) - 1;
// 			return (0);
// 		}
// 		else
// 			return (1);
// 	}
// 	else
// 	{
// 		if (tproc->wait_cycle == 1)
// 		{
// 			ret = deal_command(tmap, tproc,
// 					tproc->on_command, tproc->pc);
// 			tproc->on_command = 0;
// 			return (ret);
// 		}
// 		else
// 		{
// 			(tproc->wait_cycle)--;
// 			return (0);
// 		}
// 	}
// }
