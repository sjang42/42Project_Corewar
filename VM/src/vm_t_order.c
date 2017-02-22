/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:22:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/20 15:22:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_order.h>

t_order		*t_order_new(int size)
{
	t_order *torder;

	torder = (t_order*)malloc(sizeof(t_order));
	torder->idx_cham = (int*)malloc(sizeof(int) * size);
	torder->idx_tproc = (int*)malloc(sizeof(int) * size);
	torder->mem_order = size;
	torder->size_order = 0;
	return (torder);
}

void	t_order_store(t_order *torder, int idx_cham, int idx_tproc)
{
	if (torder->size_order + 2 > torder->mem_order)
	{
		torder->idx_cham = (int*)ft_realloc(torder->idx_cham,
								sizeof(int) * torder->mem_order,
								sizeof(int) * (torder->mem_order + 15));
		torder->idx_tproc = (int*)ft_realloc(torder->idx_tproc,
								sizeof(int) * torder->mem_order,
								sizeof(int) * (torder->mem_order + 15));
		torder->mem_order += 15;
	}
	torder->idx_cham[torder->size_order] = idx_cham;
	torder->idx_tproc[torder->size_order] = idx_tproc;
	torder->size_order += 1;
}

//I think this function has some error..... makin segfault.

int		t_order_delete(t_order *torder, int idx_cham, int idx_tproc)
{
	int i;

	i = 0;
	while (i < torder->size_order)
	{
		if (torder->idx_cham[i] == idx_cham &&
			torder->idx_tproc[i] == idx_tproc)
			break ;
		i++;
	}
	if (i == torder->size_order)
	{
		printf("yup2\n");
		return (-1);
	}
	while (i < torder->size_order - 1)
	{
		torder->idx_cham[i] = torder->idx_cham[i + 1];
		if (torder->idx_cham[i] == idx_cham)
			torder->idx_tproc[i] = torder->idx_tproc[i + 1] - 1;
		else
			torder->idx_tproc[i] = torder->idx_tproc[i + 1];
		i++;
	}
	// ft_memmove(&(torder->idx_cham[i]),
	// 			&(torder->idx_cham[i + 1]),
	// 			(sizeof(int) * (torder->size_order - (i + 1))));
	// ft_memmove(&(torder->idx_tproc[i]),
	// 			&(torder->idx_tproc[i + 1]),
	// 			(sizeof(int) * (torder->size_order - (i + 1))));
	torder->size_order -= 1;
	return (i);
}
