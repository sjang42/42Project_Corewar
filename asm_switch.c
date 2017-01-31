/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 20:47:29 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 20:47:30 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	switch_inst_sub(char *str)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(str, "xor"))
		ret = XOR;
	else if (!ft_strcmp(str, "zjmp"))
		ret = ZJMP;
	else if (!ft_strcmp(str, "ldi"))
		ret = LDI;
	else if (!ft_strcmp(str, "sti"))
		ret = STI;
	else if (!ft_strcmp(str, "fork"))
		ret = FORK;
	else if (!ft_strcmp(str, "lld"))
		ret = LLD;
	else if (!ft_strcmp(str, "lldi"))
		ret = LLDI;
	else if (!ft_strcmp(str, "lfork"))
		ret = LFORK;
	else if (!ft_strcmp(str, "aff"))
		ret = AFF;
	return (ret);
}

int		switch_inst(char *src)
{
	char	*str;
	int		ret;

	ret = 0;
	if (!ft_strcmp(str, "live"))
		ret = LIVE;
	else if (!ft_strcmp(str, "ld"))
		ret = LD;
	else if (!ft_strcmp(str, "st"))
		ret = ST;
	else if (!ft_strcmp(str, "add"))
		ret = ADD;
	else if (!ft_strcmp(str, "sub"))
		ret = SUB;
	else if (!ft_strcmp(str, "and"))
		ret = AND;
	else if (!ft_strcmp(str, "or"))
		ret = OR;
	else
		ret = switch_inst_sub(str);
	return (ret);
}
