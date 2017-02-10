/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:01:39 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 16:01:40 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	draw_repeat_ch_hor(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x, y + i);
		waddch(win, ch);
		i++;
	}
}

void	draw_repeat_ch_ver(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x + i, y);
		waddch(win, ch);
		i++;
	}
}


int		check_arg_byte(int opcode, int *arg_byte)
{
	int ret;

	if (!arg_byte)
		return (-1);
	ret = 0;
	if (
		(
			opcode == op_tab[OP_LD].opcode ||
			opcode == op_tab[OP_LLD].opcode
		)
		&&
		(
			(
				arg_byte[0] != T_DIR &&
				arg_byte[0] != T_IND
			)
			||
				arg_byte[1] != T_REG
		)
		)
		ret = -1;
	else if (
				opcode == op_tab[OP_ST].opcode
			&&
				(
						arg_byte[0] != T_REG
					||
					(
						arg_byte[1] != T_REG &&
						arg_byte[1] != T_IND
					)
				)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_ADD].opcode ||
				opcode == op_tab[OP_SUB].opcode)
			&&
			(	
				arg_byte[0] != T_REG ||
				arg_byte[1] != T_REG ||
				arg_byte[2] != T_REG)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_AND].opcode ||
				opcode == op_tab[OP_OR].opcode ||
				opcode == op_tab[OP_XOR].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG &&
					arg_byte[0] != T_DIR &&
					arg_byte[0] != T_IND
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR &&
					arg_byte[1] != T_IND
				)
				||
					arg_byte[2] != T_REG
			)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_LDI].opcode ||
				opcode == op_tab[OP_LLDI].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG &&
					arg_byte[0] != T_DIR &&
					arg_byte[0] != T_IND
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR
				)
				||
					arg_byte[2] != T_REG
			)
			)
		ret = -1;
	else if (
			(
				opcode == op_tab[OP_STI].opcode
			)
			&&
			(
				(
					arg_byte[0] != T_REG
				)
				||
				(
					arg_byte[1] != T_REG &&
					arg_byte[1] != T_DIR
					arg_byte[1] != T_IND
				)
				||
					arg_byte[2] != T_DIR &&
					arg_byte[2] != T_REG
			)
			)
		ret = -1;

	else if (
			(
				opcode == op_tab[OP_LD].opcode
			)
			&&
				(
					(
						arg_byte[0] != T_DIR &&
						arg_byte[0] != T_IND
					)
					||
						arg_byte[1] != T_REG
				)
			)
		ret = -1;
	return (ret);
}
