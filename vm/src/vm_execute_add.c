/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_execute_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:03:57 by sjang             #+#    #+#             */
/*   Updated: 2017/02/05 19:03:58 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>


t_arg		*get_ret_targ(t_map *tmap, int *ret, int opcode, int pc_command)
{
	t_arg	*targ;

	*ret = count_bytecode_cycle(tmap, opcode, pc_command) +
								op_tab[opcode - 1].num_bytecode + 1;
	targ = t_arg_new(tmap, pc_command, opcode);
	if (targ == NULL)
		return (NULL);
	else
		return (targ);
}

int			read_rgies(t_proc *tproc, t_arg *targ, t_type_arg *type_arg)
{
	if (read_registry(tproc->registry,
						((char*)(targ->arg))[0],
						&(type_arg->val_reg[0]))
		||
		read_registry(tproc->registry,
						((char*)(targ->arg))[1],
						&(type_arg->val_reg[1]))
		||
		read_registry(tproc->registry,
						((char*)(targ->arg))[2],
						&(type_arg->val_reg[2]))
		)
	{
		return (-1);
	}
	else
		return (0);
}

int		deal_add(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc)
{
	t_arg			*targ;
	t_type_arg		type_arg;
	int				ret;

	if ((targ = get_ret_targ(tmap, &ret, OP_ADD + 1, pc_command)) == NULL)
		return (ret);
	if (read_rgies(tproc, targ, &type_arg) == -1)
	{
		t_arg_destroy(targ);
		return (ret);
	}
	type_arg.val_reg[3] = type_arg.val_reg[0] + type_arg.val_reg[1];
	if (put_registry(tproc->registry, ((char*)(targ->arg))[2],
					&(type_arg.val_reg[3])))
	{
		t_arg_destroy(targ);
		return (ret);
	}
	tproc->carry = (type_arg.val_reg[3] == 0) ? 1 : 0;
	if (tarena->option & COMMANDS)
		show_commands_add(tproc, targ);
	t_arg_destroy(targ);
	return (ret);
}
