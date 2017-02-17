/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_label.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:23:58 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 15:23:59 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_T_LABEL_H
# define ASM_T_LABEL_H

# include <libft.h>
# include <asm_t_inst.h>

typedef struct	s_label_node
{
	char	*name;
	int		idx;
}				t_label_node;

typedef struct	s_label
{
	t_label_node	*label;
	int				size_label;
	int				mem_label;
}				t_label;

typedef struct	s_label_variable
{
	char		*first;
	char		**arg;
	t_inst		*tinst;
	char		*tmp;
	int			i;
}				t_label_variable;

t_label			*t_label_new(int size);
int				t_label_isexist(t_label *tlabel, char const *src);
int				t_label_put(t_label *tlabel, char const *src, int idx);
void			t_label_destroy(t_label *tlabel);

#endif
