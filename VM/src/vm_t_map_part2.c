/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_map_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 23:37:17 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 23:37:19 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

int		t_map_put_chams(t_map *tmap, t_champion **tcham, int num_cham)
{
	int				i;
	int				where;
	unsigned int	j;

	i = 0;
	tmap->num_cham = num_cham;
	while (i < num_cham)
	{
		where = ((MEM_SIZE) / num_cham * i);
		tcham[i]->tproc[0]->pc = where;
		ft_memcpy(tmap->map + where,
			((tcham[i])->tinst).inst,
			((tcham[i])->theader).prog_size);
		j = 0;
		while (j < tcham[i]->theader.prog_size)
		{
			tmap->possession[where + j] = i;
			j++;
		}
		i++;
	}
	return (0);
}

int		t_map_put_bytes(t_map *tmap, int where, void *bytes, int size)
{
	char	*to_put;
	int		i;

	to_put = (char*)bytes;
	i = 0;
	while (i < size)
	{
		ft_memcpy(
			tmap->map + ((where + i) % MEM_SIZE),
			bytes + i,
			1);
		i++;
	}
	return (0);
}

void	w_sti_reg_to_map(t_arena *tarena, int idx_cham, int where, void *bytes)
{
	char	*to_put;
	int		i;
	char	*dup_bytes;

	to_put = (char*)bytes;
	if (where < 0)
		where += (MEM_SIZE);
	dup_bytes = (char*)malloc(sizeof(char) * REG_SIZE);
	ft_memcpy(dup_bytes, bytes, REG_SIZE);
	ft_endian_convert(dup_bytes, REG_SIZE);
	i = 0;
	while (i < REG_SIZE)
	{
		ft_memcpy(
			tarena->tmap->map + ((where + i) % MEM_SIZE),
			dup_bytes + i,
			1);
		ft_memcpy(
			tarena->tmap->possession + ((where + i) % MEM_SIZE),
			&(idx_cham),
			1);
		i++;
	}
	free(dup_bytes);
}
