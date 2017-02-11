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
			tmap->possession[where + j] = i;
			j++;
		}
		i++;
	}
	return (0);
}

void	w_sti_reg_to_map(t_arena *tarena, int idx_cham, int where, void *bytes)
{
	char	*to_put;
	int		i;
	char *dup_bytes;

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

// int		w_t_map_put_bytes(t_arena *tarena, int idx_cham,
// 							int where, void *bytes);
// 	// int where, void *bytes, int size)
// {
// 	char	*to_put;
// 	int		i;
// 	unsigned char cham_num;

// 	to_put = (char*)bytes;
// 	cham_num = (unsigned char)(tarena->tcham[idx_cham]->number + 1);
// 	i = 0;
// 	while (i < REG_SIZE)
// 	{
// 		ft_memcpy(
// 			tarena->tmap->map + ((where + i) % MEM_SIZE),
// 			bytes + i,
// 			1);
// 		ft_memcpy(
// 			tarena->tmap->possession + ((where + i) % MEM_SIZE),
// 			&(cham_num),
// 			1);
// 		i++;
// 	}
// 	return (0);
// }

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











