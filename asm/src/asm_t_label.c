/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_t_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:53:20 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 14:53:21 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_t_label.h>
#include <op.h>

t_label		*t_label_new(int size)
{
	t_label		*tlabel;

	tlabel = (t_label*)malloc(sizeof(t_label));
	tlabel->label = (t_label_node*)malloc(sizeof(t_label_node) * size);
	tlabel->mem_label = size;
	tlabel->size_label = 0;
	return (tlabel);
}

#include <stdio.h>///


int			t_label_isexist(t_label *tlabel, char const *src)
{
	int		i;
	char	*dup;
	char	*tmp;

	i = 0;
	dup = ft_strdup(src);
	tmp = ft_strchr(dup, LABEL_CHAR);
	if (tmp)
		*tmp = 0;
	while (i < tlabel->size_label)
	{
		if (!ft_strcmp(tlabel->label[i].name, dup))
		{
			free(dup);
			return (1);
		}
		i++;
	}
	free(dup);
	return (0);
}

int			t_label_put(t_label *tlabel, char const *src, int idx)
{
	char *tmp;

	if (t_label_isexist(tlabel, src))
		return (0);
	if (tlabel->size_label + 5 >= tlabel->mem_label)
	{
		tlabel->label =
		(t_label_node*)ft_realloc(tlabel->label,
			sizeof(t_label_node) * tlabel->mem_label,
			sizeof(t_label_node) * (tlabel->mem_label * 100));
		tlabel->mem_label += 100;
	}
	tlabel->label[tlabel->size_label].name = ft_strdup(src);
	tmp = ft_strchr(tlabel->label[tlabel->size_label].name, LABEL_CHAR);
	if (tmp)
		*tmp = '\0';
	tlabel->label[tlabel->size_label].idx = idx;
	tlabel->size_label += 1;
	return (1);
}

int			t_label_get_idx(t_label *tlabel, char const *name)
{
	int i;

	i = 0;
	while (i < tlabel->size_label)
	{
		if (!ft_strcmp(tlabel->label[i].name, name))
			return (tlabel->label[i].idx);
		i++;
	}
	return (-1);
}
