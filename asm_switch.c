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

static int	switch_instruction_sub(char **strsplit)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(strsplit[0], "xor"))
		ret = XOR;
	else if (!ft_strcmp(strsplit[0], "zjmp"))
		ret = ZJMP;
	else if (!ft_strcmp(strsplit[0], "ldi"))
		ret = LDI;
	else if (!ft_strcmp(strsplit[0], "sti"))
		ret = STI;
	else if (!ft_strcmp(strsplit[0], "fork"))
		ret = FORK;
	else if (!ft_strcmp(strsplit[0], "lld"))
		ret = LLD;
	else if (!ft_strcmp(strsplit[0], "lldi"))
		ret = LLDI;
	else if (!ft_strcmp(strsplit[0], "lfork"))
		ret = LFORK;
	else if (!ft_strcmp(strsplit[0], "aff"))
		ret = AFF;
	return (ret);
}

int		switch_instruction(char *str)
{
	char	**strsplit;
	int		ret;

	ret = 0;
	if (str[ft_strlen(str) - 1] == LABEL_CHAR)
		return (LABEL);
	strsplit = ft_strsplit(str, ' ');
	if (!ft_strcmp(strsplit[0], "live"))
		ret = LIVE;
	else if (!ft_strcmp(strsplit[0], "ld"))
		ret = LD;
	else if (!ft_strcmp(strsplit[0], "st"))
		ret = ST;
	else if (!ft_strcmp(strsplit[0], "add"))
		ret = ADD;
	else if (!ft_strcmp(strsplit[0], "sub"))
		ret = SUB;
	else if (!ft_strcmp(strsplit[0], "and"))
		ret = AND;
	else if (!ft_strcmp(strsplit[0], "or"))
		ret = OR;
	else
		ret = switch_instruction_sub(strsplit);
	ft_destroy_strsplit(strsplit);
	return (ret);
}