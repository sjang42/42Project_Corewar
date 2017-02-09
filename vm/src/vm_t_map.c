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

	i = 0;
	tmap = (t_map*)malloc(sizeof(t_map));
	tmap->map = (char*)malloc(sizeof(char) * size);
	tmap->possession = (char*)malloc(sizeof(char) * size);
	tmap->color = (char*)malloc(sizeof(char) * size);
	ft_bzero(tmap->map, size);
	ft_bzero(tmap->possession, size);
	ft_bzero(tmap->color, size);
	tmap->size_map = size;
	tmap->num_cham = 0;
	return (tmap);
}

int		t_map_put_one(t_map *tmap, int fd, int start)
{
	char	*str;
	int check;

	if (fd < 0)
		return (-1);
	check = ft_read_all(fd, &str);
	if (check == -1)
		ft_exit_error("Wrong file");
	if (ft_strlen(str) > tmap->size_map)
		ft_exit_error("File length is too long");
	ft_memcpy(tmap->map + start,
				str + LENGTH_BEFORE_INST,
				check - (LENGTH_BEFORE_INST));
	free(str);
	return (0);
}

int 	t_map_put_all(t_map *tmap, int fd[], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		t_map_put_one(tmap, fd[i], ((MEM_SIZE) / size * i));
		i++;
	}
	return (0);
}

int		t_map_put_chams(t_map *tmap, t_champion **tcham, int num_cham)
{
	int 	i;
	int		where;
	int		j;

	i = 0;
	tmap->num_cham = num_cham;
	while (i < num_cham)
	{
		where = ((MEM_SIZE) / num_cham * i);
		tcham[i]->tproc[0].pc = where;
		ft_memcpy(tmap->map + where,
			((tcham[i])->tinst).inst,
			((tcham[i])->theader).prog_size);
		j = 0;
		while (j < tcham[i]->theader.prog_size)
		{
			tmap->possession[where + j] = tcham[i]->number + 1;
			tmap->color[where + j] = tcham[i]->number + 1;
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

void	t_map_destroy(t_map *tmap)
{
	free(tmap->map);
	free(tmap->possession);
	free(tmap->color);
	free(tmap);
}











