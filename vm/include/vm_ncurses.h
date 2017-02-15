/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 23:42:19 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 23:42:21 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_NCURSES_H
# define VM_NCURSES_H

# include <vm_t_map.h>
# include <vm_structures.h>
# include <ncurses.h>
# include <op.h>

#include <stdio.h>//

# define CONTENTS_BYTES_PER_LINE		(64)
# define CONTENTS_CHARS_PER_LINE		(CONTENTS_BYTES_PER_LINE * 3 - 1)
# define CONTENTS_LINES_FOR_MEM			(MEM_SIZE / CONTENTS_BYTES_PER_LINE)

# define CONTENTS_CHARS_PREFIX_HOR		2
# define CONTENTS_CHARS_SUFFIX_HOR		2

# define CONTENTS_CHARS_PREFIX_VER		1
# define CONTENTS_CHARS_SUFFIX_VER		2

# define INFO_CHARS						56

# define CONTENTS_TOTAL_COLS			(CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_SUFFIX_HOR + 2)

# define CONTENTS_TOTAL_LINES			(CONTENTS_CHARS_PREFIX_VER +\
										CONTENTS_LINES_FOR_MEM +\
										CONTENTS_CHARS_SUFFIX_VER + 2)




# define INFO_TOTAL_COLS				(INFO_CHARS + 2)

# define INFO_TOTAL_LINES				(CONTENTS_CHARS_PREFIX_VER +\
										CONTENTS_LINES_FOR_MEM +\
										CONTENTS_CHARS_SUFFIX_VER + 2)



# define DIVIDE_VER_FIRST				(0)
# define DIVIDE_VER_SECOND				(1 + CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_SUFFIX_HOR)

# define DIVIDE_VER_THIRD				(1 + CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_SUFFIX_HOR + 1 +\
										INFO_CHARS)

# define DIVIDE_HOR_FIRST				(0)
# define DIVIDE_HOR_SECOND				(1 + CONTENTS_CHARS_PREFIX_VER +\
										CONTENTS_LINES_FOR_MEM +\
										CONTENTS_CHARS_SUFFIX_VER)

# define CONTENTS_START_Y				(1 + CONTENTS_CHARS_PREFIX_VER)
# define CONTENTS_START_X				(1 + CONTENTS_CHARS_PREFIX_HOR)

# define TERM_SAYS_Y					(CONTENTS_TOTAL_LINES - 2)
# define TERM_SAYS_X					(3)
# define TERM_SAYS_MASSAGE				"Term says : "
# define TERM_SAYS_MASSAGE_LEN			(12)

# define AFF_Y							(TERM_SAYS_Y - 1)
# define AFF_X							(3)
# define AFF_MASSAGE					"AFF : "
# define AFF_MASSAGE_LEN				(6)

# define INFO_PAUSED_LEN				(13)
# define INFO_PAUSED_Y					(2)
# define INFO_PAUSED_X					((INFO_TOTAL_COLS - INFO_PAUSED_LEN) / 2)


# define INFO_CYCLE_LEN					(14)
# define INFO_CYCLE_Y					(7)
# define INFO_CYCLE_X					((INFO_TOTAL_COLS - INFO_CYCLE_LEN) / 2)

# define INFO_PROCESSES_LEN				(14)
# define INFO_PROCESSES_Y				(9)
# define INFO_PROCESSES_X				((INFO_TOTAL_COLS - INFO_PROCESSES_LEN) / 2)


# define INFO_NAME_LEN					(20)
# define INFO_NAME_NUM_X				(34)

# define INFO_NAME_CHAM1_Y				(15)
# define INFO_NAME_CHAM1_X				(3)

# define INFO_CYCLE_DIE_LEN				(15)
# define INFO_CYCLE_DIE_X				(INFO_NAME_CHAM1_X)
# define INFO_CYCLE_DIE_NUM_X			(INFO_CYCLE_DIE_X + INFO_CYCLE_DIE_LEN)




# define COLORS_BACKGOUND				COLOR_BLACK
# define RGB_CHAM1						0, 255, 0
# define RGB_CHAM2						0, 0, 255
# define RGB_CHAM3						255, 0, 0
# define RGB_CHAM4						255, 255, 0
# define RGB_CHAM5						255, 0, 255
# define RGB_CHAM6						0, 255, 255

void			ncur_box(WINDOW *win);
void			ncur_map_init(WINDOW *win, t_map *tmap, t_arena *tarena);

t_windows		*ncur_new(t_arena *tarena);



void		colors_init(WINDOW *win);
int 		colors_set_pc(WINDOW *win, t_arena *tarena, int pc);
int 		colors_off_pc(WINDOW *win, t_arena *tarena, int pc);
void		ncur_unhighlight_pc(WINDOW *win, t_map *tmap, t_proc *tproc, t_arena *tarena);
void		ncur_highlight_pc(WINDOW *win, t_map *tmap, t_proc *tproc, t_arena *tarena);
void		ncur_finish(t_windows *twin);

void			ncur_show_termsays(WINDOW *win_arena);
void			ncur_erase_termsays(WINDOW *win);

/*
**	INFO
*/
void			info_show_cycle(WINDOW *win_info, int cycle);
void			info_show_status(WINDOW *win_info, int stop);
void			info_show_cham_init(WINDOW *win_info, t_arena *tarena);
void			info_show_process(WINDOW *win_info, int num_process);

void			info_show_cham_lastlive(WINDOW *win_info, t_arena *tarena, int idx_cham);
void			info_show_cham_live_current(WINDOW *win_info, t_arena *tarena, int idx_cham);

void			ncur_show_aff(WINDOW *win_arena, int idx_cham, char byte);
void			ncur_show_live(WINDOW *win_arena, t_arena *tarena, int idx_cham, int live_cham);

void		w_ft_displaybyte(WINDOW *win, int y, int x, unsigned char ptr);

void		ncur_map_update(t_arena *tarena, int pc, int size);

void			info_show_cycle_die_period(WINDOW *win_info, t_arena *tarena);
void			info_show_constants(WINDOW *win_info, t_arena *tarena);

#endif




