/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:44:16 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 19:44:17 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

void		ft_remove_overlap(char **pstr, char ch)
{
	size_t	len_origin;
	int		start;
	int		end;
	char	*str;

	str = *pstr;
	len_origin = ft_strlen(str);
	start = 0;
	while (str[start])
	{
		while (str[start] != ch && str[start])
			start++;
		end = start;
		while (str[end] == ch)
			end++;
		if (end != start)
			ft_memmove(str + start + 1, str + end, ft_strlen(str + end) + 1);
		start++;
	}
	*pstr = (char*)ft_realloc(
			*pstr,
			(len_origin + 1) * sizeof(char),
			(ft_strlen(str) + 1) * sizeof(char));
}

int		ft_endian_ltob(void *src, size_t size)
{
	size_t	i;
	char	*src_cp;
	char	tmp;

	src_cp = (char*)src;
	i = 0;
	while (i < size / 2)
	{
		tmp = src_cp[size - 1 - i];
		src_cp[size - 1 - i] = src_cp[i];
		src_cp[i] = tmp;
		i++;
	}
	return (0);
}

void	ft_destroy_strsplit(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}
