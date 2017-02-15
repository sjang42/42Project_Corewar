/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:53:52 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 18:53:53 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		fill_one_arg(char *command, char *arg, t_inst *tinst, t_label *tlabel)
{
	char	mem[4];
	int		num_byte;

	ft_bzero(mem, 4);
	num_byte = decide_num_byte(command, arg);
	t_inst_put(tinst, mem, num_byte);
}

int			fill_command(char *command, char **arg,
						t_inst *tinst, t_label *tlabel)
{
	int		i;
	char	opcode;
	char 	zero;

	zero = 0;
	if (check_command(command, arg))
		return (-1);
	opcode = (char)switch_inst(command);
	t_inst_put(tinst, &zero, 1);
	if (op_tab[opcode - 1].num_bytecode)
		t_inst_put(tinst, &zero, 1);
	i = 0;
	while (i < op_tab[opcode - 1].num_arg)
	{
		fill_one_arg(command, arg[i], tinst, tlabel);
		i++;
	}
	return (0);
}

t_label		*get_label(t_strs *tstrs)
{
	int			i;
	int			j;
	t_inst		*tinst;
	t_label		*tlabel;
	char		*first;
	char		*tmp;
	char		**arg;

	tinst = t_inst_new(100);
	tlabel = t_label_new(100);
	i = 2;
	while (i < tstrs->size_strarr)
	{
		first = ft_strdup(tstrs->strarr[i]);
		if (switch_type(first) == T_LAB)
			t_label_put(tlabel, first, tinst->size_inst);
		else if ((tmp = ft_strchr(first, ' ')))
		{
			*tmp = 0;
			arg = ft_strsplit(tmp + 1, SEPARATOR_CHAR);
			j = 0;
			while (arg && arg[j])
			{
				tmp = ft_strtrim(arg[j]);
				free(arg[j]);
				arg[j] = tmp;
				j++;
			}
			if (!arg ||
				fill_command(first, arg, tinst, tlabel) == -1)
			{
				free(first);
				ft_destroy_strsplit(arg);
				strs_destroy(tstrs);
				t_label_destroy(tlabel);
				t_inst_destroy(&tinst);
				ft_exit_error("Syntax error1");
			}
			ft_destroy_strsplit(arg);
		}
		else
		{
			free(first);
			ft_destroy_strsplit(arg);
			strs_destroy(tstrs);
			t_label_destroy(tlabel);
			t_inst_destroy(&tinst);
			ft_exit_error("Syntax error2");
		}
		free(first);
		i++;
	}
	t_inst_destroy(&tinst);
	return (tlabel);
}
