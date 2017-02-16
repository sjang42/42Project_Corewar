/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:23:19 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 15:23:20 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		show_inst(t_inst *tinst)
{
	int i;

	i = 0;
	while (i < tinst->size_inst)
	{
		printf("%x ", (unsigned char)tinst->inst[i]);
		i++;
	}
}

int			*get_bytecodes(t_map *tmap, int pc_command, int opcode)
{
	int		*bytecode;
	int		i;

	if (op_tab[opcode - 1].num_bytecode == 0)
	{
		bytecode = (int*)malloc(sizeof(int) * op_tab[opcode - 1].num_arg);
		i = 0;
		while (i < op_tab[opcode - 1].num_arg)
		{
			bytecode[i] = op_tab[opcode - 1].argument[i];
			i++;
		}
	}
	else
		bytecode = read_bytecode(
					tmap, pc_command,
					op_tab[opcode - 1].num_arg);
	return (bytecode);
}
