/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_t_inst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:28:24 by sjang             #+#    #+#             */
/*   Updated: 2017/01/31 15:28:25 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_T_INST_H
# define ASM_T_INST_H

# include <libft.h>

typedef struct  s_inst
{
    char    *inst;
    int     size_inst;
    int     mem_inst;
}               t_inst;

t_inst          *t_inst_new(int size);
void            t_inst_put(t_inst *tinst, void const *src, int size);
void            t_inst_destroy(t_inst **tinst);

#endif
