/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_t_strs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:27:28 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 15:27:29 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_T_STRS_H
# define ASM_T_STRS_H

# include <libft.h>

typedef struct	s_strs
{
	char	**strarr;
	int		size_mem;
	int		size_strarr;
}				t_strs;

t_strs			*strs_new(size_t size_mem);
int				strs_addone(t_strs *strs, char *str);
void			strs_destroy(t_strs *strs);

#endif
