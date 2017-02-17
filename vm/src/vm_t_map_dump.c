/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_map_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 19:46:05 by sjang             #+#    #+#             */
/*   Updated: 2017/02/09 19:46:06 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_map.h>

static void		ft_displaybyte(unsigned char ptr)
{
	int result;
	int mod;

	result = ptr / 16;
	if (result < 10)
		result += '0';
	else
		result += 'a' - 10;
	mod = ptr % 16;
	if (mod < 10)
		mod += '0';
	else
		mod += 'a' - 10;
	write(1, &result, 1);
	write(1, &mod, 1);
}

void			t_map_dump(t_map *tmap)
{
	int				i;
	char			*str;
	char			zeros[4];

	i = 0;
	ft_memset(zeros, '0', 4);
	while (i < tmap->size_map)
	{
		if (i % 64 == 0)
		{
			ft_putstr("0x");
			str = ft_itoa_base(i, 16);
			if (ft_strlen(str) < 4)
				write(1, zeros, 4 - ft_strlen(str));
			ft_putstr(str);
			ft_putstr(" : ");
			free(str);
		}
		ft_displaybyte(tmap->map[i]);
		ft_putchar(' ');
		if ((i + 1) % 64 == 0 || (i + 1) == tmap->size_map)
			ft_putchar('\n');
		i++;
	}
}
