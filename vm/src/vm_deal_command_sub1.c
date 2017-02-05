/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_deal_command_sub1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:04:47 by sjang             #+#    #+#             */
/*   Updated: 2017/02/03 14:04:48 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void	*read_data(t_map *tmap, int pc, size_t size)
{
	char		*ret;
	size_t		i;

	ret = (char*)malloc(sizeof(char) * size);
	i = 0;
	while (i < size)
	{
		ret[i] = read_current_byte(tmap, pc + i);
		i++;
	}
	return ((void*)ret);
}

int		put_registry(char **registry, int idx, void *src)
{
	if (!registry || !*registry ||
		idx < 1 || idx > REG_NUMBER)
		return (0);
	ft_memcpy(registry[idx - 1], src, REG_SIZE);
	return (1);
}

char 	read_current_byte(t_map *tmap, int pc)
{
	return (tmap->map[pc % (MEM_SIZE)]);
}

char	read_indirect_data(t_map *tmap, int pc_command, int idx)
{
	return (read_current_byte(tmap, (pc_command + idx) % (MEM_SIZE)));
}
