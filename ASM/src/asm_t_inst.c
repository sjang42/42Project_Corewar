/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_t_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:52:07 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 14:52:08 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_t_inst.h>

t_inst		*t_inst_new(int size)
{
	t_inst	*tinst;

	tinst = (t_inst*)malloc(sizeof(t_inst));
	tinst->inst = (char*)malloc(sizeof(char) * size);
	ft_bzero(tinst->inst, size);
	tinst->mem_inst = size;
	tinst->size_inst = 0;
	return (tinst);
}

void		t_inst_put(t_inst *tinst, void const *src, int size)
{
	if (size <= 0)
		return ;
	if (tinst->size_inst + size >= tinst->mem_inst)
	{
		tinst->inst =
		(char*)ft_realloc(tinst->inst,
			sizeof(char) * tinst->mem_inst,
			sizeof(char) * (tinst->mem_inst + 100 + size));
		ft_bzero(tinst->inst + tinst->mem_inst, 100 + size);
		tinst->mem_inst += 100 + size;
	}
	ft_memcpy(tinst->inst + tinst->size_inst, src, (size_t)size);
	tinst->size_inst += size;
}

void		t_inst_destroy(t_inst **tinst)
{
	free((*tinst)->inst);
	free((*tinst));
	*tinst = NULL;
}
