/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:36:54 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 16:36:55 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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

static void		ft_displaydots(char *dots, size_t j)
{
	write(1, dots, j);
}

static void		ft_storedots(char *dots, unsigned char ptrch)
{
	if (ptrch >= 32 && ptrch <= 126)
		dots[0] = ptrch;
	else
		dots[0] = '.';
}

static void		ft_displayspaces(size_t j)
{
	char	spaces[40];
	size_t	total;
	int		i;

	i = 0;
	while (i < 40)
		spaces[i++] = ' ';
	total = 40;
	total -= j * 2;
	total -= j / 2;
	write(1, spaces, total);
}

void			print_memory(const void *addr, size_t size)
{
	size_t			i;
	size_t			j;
	char			dots[17];
	unsigned char	*ptr;

	ptr = (unsigned char*)addr;
	ft_bzero(dots, 17);
	i = 0;
	j = 0;
	while (i < size)
	{
		ft_displaybyte(ptr[i]);
		ft_storedots(dots + j, ptr[i]);
		j++;
		if ((i % 2) == 1)
			write(1, " ", 1);
		if ((i + 1) % 16 == 0 || (i + 1) == size)
		{
			ft_displayspaces(j);
			ft_displaydots(dots, j);
			write(1, "\n", 1);
			j = 0;
		}
		i++;
	}
}
