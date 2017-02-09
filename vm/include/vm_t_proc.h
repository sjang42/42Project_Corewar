/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_proc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:24:15 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 15:24:16 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_PROC_H
# define VM_T_PROC_H

# include <op.h>
# include <libft.h>
# include <vm_structures.h>

//첫 프로세서에는 registry를 null로 주기
t_proc			*t_proc_new(int pc, int carry, char **registry);
void			t_proc_destroy(t_proc *tproc);
void			t_proc_put(t_proc *tproc, int pc, int carry, char **registry);
#endif
