/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:10:20 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 17:10:20 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

t_map	*t_map_new(int size)
{
	int		i;
	t_map	*tmap;

	tmap = (t_map*)malloc(sizeof(t_map));
	tmap->map = (char*)malloc(sizeof(char) * size);
	tmap->possession = (char*)malloc(sizeof(char) * size);
	tmap->color = (char*)malloc(sizeof(char) * size);
	ft_bzero(tmap->map, size);
	ft_bzero(tmap->color, size);
	i = 0;
	while (i < size)
	{
		tmap->possession[i] = -1;
		i++;
	}
	tmap->size_map = size;
	tmap->num_cham = 0;
	return (tmap);
}

void	t_map_destroy(t_map *tmap)
{
	free(tmap->map);
	free(tmap->possession);
	free(tmap->color);
	free(tmap);
}
