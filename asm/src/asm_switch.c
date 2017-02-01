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

#include <asm.h>

int		switch_inst(char *src)
{
	char	*str;
	int		ret;
	int		i;

	i = 0;
	while (op_tab[i].mnemonic)
	{
		if (!ft_strcmp(op_tab[i].mnemonic, src))
			return (i + 1);
		i++;
	}
	return (0);
}
