/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structures.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 00:23:38 by sjang             #+#    #+#             */
/*   Updated: 2017/02/09 00:23:39 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUCTURES_H
# define VM_STRUCTURES_H

# include <ncurses.h>
# include <asm_t_inst.h>

typedef int		TYPE_DIR;
typedef int		TYPE_REG;
typedef short	TYPE_IND;
typedef short	TYPE_DIR_ADR;

typedef struct	s_xy
{
	int x;
	int y;
}				t_xy;

typedef struct	s_windows
{
	WINDOW *win_arena;
	WINDOW *win_info;		
}				t_windows;

typedef struct	s_proc
{
	int		pc;				//첫 프로세서는 시작 위치와 같이 초기화
	int		carry;
	char	**registry;		//첫 프로세서의 r1은 넘버와 같이 초기화
	int		on_command;
	int		wait_cycle;
	int		period_live;
	int		number;
	int		just_born;
	int		period_born;
	int		belong_idx_cham;
}				t_proc;

typedef struct		s_map
{
	char	*map;
	char	*possession;
	char	*color;
	int		size_map;
	int		num_cham;
}					t_map;

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
	int			mem_tproc;
	int			num_tproc;
	int			color;
	int			current_live;
	long long	last_live;
}				t_champion;

typedef	struct	s_arg
{
	int		num_arg;
	int		*bytecode;
	int		*bytes_arg;
	void	**arg;
}				t_arg;

typedef	struct	s_arena
{
	t_map		*tmap;
	t_champion	**tcham;
	int			num_cham;
	long long	cycle;
	int			cycle_to_die;
	int			game_done;
	int			num_period;
	int			last_reduce;
	int			last_alive_cham;
	t_windows	*twin;
	int			num_process;
	int			used_proc_num;
	int 		option;
	int			dump;
}				t_arena;

typedef struct	s_type_arg
{
	TYPE_REG		val_reg[4];
	TYPE_IND		val_ind[4];
	TYPE_DIR		val_dir[4];
	TYPE_REG		adr_reg[4];
	TYPE_IND		adr_ind[4];
	TYPE_DIR_ADR	adr_dir[4];
}				t_type_arg;

#endif