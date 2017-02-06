/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_champion_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:24:00 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 00:24:01 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_champion.h>

void			t_champion_showinfo(t_champion *tcham)
{
	int i;
	int j;
	int num;

	ft_putstr("Champion Number :\t");
	ft_putnbr(tcham->number);
	ft_putstr("\n");
	
	ft_putstr("Filename :\t\t");
	ft_putstr(tcham->tfile.fname);
	ft_putstr("\n");
	
	ft_putstr("Size :\t\t\t");
	ft_putnbr(tcham->theader.prog_size);
	ft_putstr("\n");
	
	ft_putstr("Name :\t\t\t");
	ft_putstr(tcham->theader.prog_name);
	ft_putstr("\n");
	
	ft_putstr("Comment :\t\t");
	ft_putstr(tcham->theader.comment);
	ft_putstr("\n");
	ft_putstr("\n");

	i = 0;
	while (i < tcham->num_tproc)
	{
		ft_putstr("proc num : ");
		ft_putnbr(i);
		ft_putstr("\n");
		ft_putstr("pc :\t");
		ft_putnbr(tcham->tproc[i].pc);
		ft_putstr("\n");
		ft_putstr("carry :\t");
		ft_putnbr(tcham->tproc[i].carry);
		ft_putstr("\n");
		j = 0;
		while (j < REG_NUMBER)
		{
			ft_memcpy(&num, (tcham->tproc[i]).registry[j], REG_SIZE);
			ft_putstr("[r");
			ft_putnbr(j + 1);
			ft_putstr("] : ");
			ft_putnbr(num);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
		ft_putstr("\n");
		i++;
	}
}
