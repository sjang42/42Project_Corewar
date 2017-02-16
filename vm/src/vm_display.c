/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 23:05:15 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 23:05:16 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void		display_winner(t_arena *tarena)
{
	int			idx_cham;
	int			idx_winner;
	long long	most_last_live;

	idx_cham = 0;
	idx_winner = 0;
	most_last_live = 0;
	while (idx_cham < tarena->num_cham)
	{
		if (tarena->tcham[idx_cham]->last_live >= most_last_live)
		{
			idx_winner = idx_cham;
			most_last_live = tarena->tcham[idx_cham]->last_live;
		}
		idx_cham++;
	}
	ft_putstr("“Player ");
	ft_putnbr(tarena->tcham[idx_winner]->number);
	ft_putstr(" (");
	ft_putstr(tarena->tcham[idx_winner]->theader.prog_name);
	ft_putstr(") won”\n");
}
