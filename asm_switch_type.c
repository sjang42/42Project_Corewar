/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_switch_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 10:51:29 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 10:51:30 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_register(char *str)
{
	int num;
	int i;

	if (!str || str[0] != 'r')
		return (0);
	if (!ft_isdigit(str[1]))
		return (0);
	num = ft_atoi(str + 1);
	if (num <= 0 || num > REG_NUMBER)
		return (0);
	i = 1;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (num);
}

int		is_direct(char *str)
{
	int	i;

	if (!str || str[0] != DIRECT_CHAR)
		return (0);
	if (ft_isonly_digit(str + 1))	//num
		return (1);
	if (str[1] == LABEL_CHAR)		//label
	{
		i = 2;
		while (str[i])
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
				return (0);
			i++;
		}
		return (2);
	}
	return (0);
}

int		is_indirect(char *str)
{
	int i;

	if (!str)
		return (0);
	if (ft_isonly_digit(str))
		return (1);
	if (str[0] == LABEL_CHAR)		//label
	{
		i = 1;
		while (str[i])
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
				return (0);
			i++;
		}
		return (2);
	}
	return (0);
}

int		is_label(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (i == 0 || str[i] != LABEL_CHAR)
		return (0);
	if (str[i + 1] != 0)
		return (0);
	return (1);
}

int		switch_type(char *str)
{
	if (is_register(str))
		return (T_REG);
	if (is_direct(str))
		return (T_DIR);
	if (is_indirect(str))
		return (T_IND);
	if (is_label(str))
		return (T_LAB);
	if (switch_inst(str))
		return (T_INST);
	return (0);
}
