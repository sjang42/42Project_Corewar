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
# include <vm_t_proc.h>
# include <op.h>

typedef struct	s_file
{
	char	*fname;
	int		fd;
}				t_file;

typedef struct	s_champion
{
	int			number;
	t_file		tfile;
	header_t	theader;
	t_inst		tinst;
	t_proc		*tproc;
	int			num_tproc;
}				t_champion;

t_champion		*t_champion_new(char *fname, int num);
void			t_champion_destroy(t_champion **tcham);
void			ft_champion_destroy_exit(t_champion **tcham);
void			t_champion_showinfo(t_champion *tcham);

#endif