/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arena.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 19:04:22 by sjang             #+#    #+#             */
/*   Updated: 2017/02/06 19:04:23 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_ARENA_H
# define VM_T_ARENA_H

#include <vm_t_champion.h>
#include <vm_t_map.h>

#include <stdio.h>//

/*
**	cycle_to_die는 최초 CYCLE_TO_DIE로 초기화되며, 조건이 만족될 때마다
**	CYCLE_DELTA만큼 줄어든다.
**	조건:
**
**	
**	
**	배열 cham_live는 매 사이클마다 0으로 초기화되며, 사이클 내에 라이브를 할 때마다
**	숫자가 올라간다.
**	시작시 num_cham만큼 동적할당된다.
**
**	last_live 는 live가 호출될 때마다 갱신되며, 그 당시의 cycle값을 저장한다.
*/

typedef	struct	s_arena
{
	t_map		*tmap;
	t_champion	**tcham;
	int			num_cham;
	long long	cycle;
	int			cycle_to_die;
	int			num_period;
	int			last_reduce;
	int			last_alive_cham;
}				t_arena;

t_arena 		*t_arena_new(int argc, char *argv[], int number[]);
void			t_arena_play(t_arena *tarena);
void		play_one_period(t_arena *tarena);

void			checkup_proc(t_arena *tarena);
void			checkup_nbr_live(t_arena *tarena);
void			checkup_max_checks(t_arena *tarena);

int				count_alive_cham(t_arena *tarena);

int				vm_execute_proc(t_map *tmap, t_champion *tcham, t_arena *tarena,
						int idx_proc);
#endif
