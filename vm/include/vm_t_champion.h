/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_champion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 13:08:11 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 13:08:12 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_CHAMPION_H
# define VM_T_CHAMPION_H

# include <libft.h>
# include <asm_t_inst.h>
# include <vm_t_champion.h>
# include <vm_t_header.h>
# include <vm_t_proc.h>
# include <op.h>
# include <vm_structures.h>

t_champion		*t_champion_new(char *fname, int num, int color, int proc_num);
// t_champion		*t_champion_new(char *fname, int num, int color);
// void			t_champion_destroy(t_champion **tcham);
void			t_champion_destroy_exit(t_champion *tcham);
void			t_champion_showinfo(t_champion *tcham);

void			t_champion_add_proc(t_champion *tcham, int idx_proc, int pc, int proc_num);
// void			t_champion_add_proc(t_champion *tcham, int idx_proc, int pc);
int				t_champion_kill_proc(t_champion *tcham, int idx_proc);

void			t_champion_destroy(t_champion *tcham);


#endif