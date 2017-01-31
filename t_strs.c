/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:05:52 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 12:05:52 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_strs		*strs_new(size_t size_mem)
{
	t_strs	*strs;

	strs = (t_strs*)malloc(sizeof(t_strs));
	strs->strarr = (char**)malloc(sizeof(char*) * size_mem);
	ft_bzero(strs->strarr, sizeof(char*) * size_mem);
	strs->size_mem = size_mem;
	strs->size_strarr = 0;
	return (strs);
}

int			strs_addone(t_strs *strs, char *str)
{
	if (strs->size_strarr + 5 > strs->size_mem)
	{
		strs->strarr = (char**)
						ft_realloc(strs->strarr,
						sizeof(char*) * strs->size_mem,
						sizeof(char*) * (strs->size_mem + 100));
		strs->size_mem += 100;
	}
	strs->strarr[strs->size_strarr] = ft_strdup(str);
	strs->size_strarr += 1;
	return (0);
}
