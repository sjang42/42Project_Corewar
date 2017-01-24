/*
** machine.h for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 15:06:25 2014 chapui_s
** Last update Sat Apr 12 18:37:15 2014 chapui_s
*/

#ifndef MACHINE_H_
# define MACHINE_H_

# include "SDL/SDL.h"
# include "SDL/SDL_ttf.h"
# include "../op/op.h"

typedef struct		s_instruction
{
  unsigned char		code;
  unsigned char		type;
  int			params[4];
}			t_instruction;

typedef struct		s_champions
{
  char			*filename;
  int			size;
  unsigned int		prog_number;
  unsigned int		load_address;
  char			*name;
  char			*comment;
  int			*reg;
  int			pc;
  unsigned int		carry;
  unsigned int		last_live;
  int			cycle_to_wait;
  int			color_gui;
  struct s_champions	*next;
}			t_champions;

typedef struct		s_corewar
{
  unsigned char		*arena;
  unsigned char		*info_arena;
  unsigned int		nb_champions;
  t_champions		*champions;
  t_champions		*last_champions;
  int			last_live_nb;
  char			*last_live_name;
  int			prog_number_max;
  unsigned long long	nbr_cycle_dump;
  int			nbr_live_cur;
  int			is_desassembler;
  int			cycle_to_die_cur;
}			t_corewar;

typedef struct		s_gui
{
  SDL_Surface		*screen;
  SDL_Surface		*byte_arena;
  SDL_Surface		*background;
  SDL_Surface		*players[5];
  TTF_Font		*font;
  TTF_Font		*font_info;
  int			*list_pc;
  SDL_Rect		pos_background;
  SDL_Color		my_color;
}			t_gui;

typedef struct		s_functions
{
  int			numero;
  int			(*function)(t_corewar *core,
				    t_champions *champions,
				    t_instruction *instruction);
}			t_functions;

# define ALLOC_FAILED	"error: could not alloc\n"
# define LIVE		(1)
# define LD		(2)
# define ST		(3)
# define ADD		(4)
# define SUB		(5)
# define AND		(6)
# define OR		(7)
# define XOR		(8)
# define ZJMP		(9)
# define LDI		(10)
# define STI		(11)
# define FORK		(12)
# define LLD		(13)
# define LLDI		(14)
# define LFORK		(15)
# define AFF		(16)
# define WIN_X		(1345)
# define WIN_Y		(800)
# define MAX_PC		(15000)

int			usage(void);
int			my_putstr(char *s, int fd);
int			get_args(int argc, char **argv, t_corewar *core);
int			is_numbers(char *s);
int			is_options(char *s);
int			my_strcmp(char *s1, char *s2);
int			is_file_dot_cor(char *s);
int			is_one_file_cor(int argc, char **argv);
int			push_champion(t_corewar *core,
				      char *filename,
				      unsigned int prog_number,
				      unsigned int load_address);
unsigned int		my_unsigned_atoi(char *str);
int			attribute_prog_number(t_champions *list_champions,
					      unsigned int nb_champions);
int			attribute_address(t_champions *list_champions,
					  unsigned int nb_champions);
int			load_arena(t_corewar *core);
void			init_arena(unsigned char *ptr, unsigned int size, int value);
void			my_putchar(char c);
int			load_champions_in_arena(unsigned char *arena,
						unsigned char *info_arena,
						t_corewar *core);

int			my_showmem(unsigned char *str, int size);
int			my_gui(t_corewar *core, char *exec_name);
int			get_image_path(t_gui *gui, char *exec_path);
char			*hex_to_str(unsigned char c, char *str);
int			get_color(t_gui *gui,
				  t_corewar *core,
				  int i);
int			get_name_comment_champions(t_champions *champions,
						   int *fd);
int			my_strlen(char *s);
char			*my_strcat(char *s1, char *s2);
void			get_instruction(t_corewar *core,
					t_champions *champions,
					t_instruction *instruction);
int			exec_instructions(t_corewar *core,
					  t_champions *champions);
int			my_live(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_ld(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_lld(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_st(t_corewar *core,
			      t_champions *champions,
			      t_instruction *instruction);
int			my_add(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_sub(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_and(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_or(t_corewar *core,
			      t_champions *champions,
			      t_instruction *instruction);
int			my_xor(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_ldi(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_lldi(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_sti(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			my_zjmp(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_fork(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_lfork(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction);
int			my_aff(t_corewar *core,
			       t_champions *champions,
			       t_instruction *instruction);
int			read_arena(t_corewar *core, int index, int n_to_read);
void			write_arena_four(t_corewar *core,
					 t_champions *champions,
					 int to_write,
					 int index);
int			is_direct(int octet_type, int num_param);
int			is_indirect(int octet_type, int num_param);
int			is_register(unsigned char octet_type, int num_param);
int			is_good_register(int nb);
int			manage_instructions(t_corewar *core);
int			disp_info_players(t_corewar *core,
					  t_gui *gui,
					  int cycles,
					  int pause);
char			*int_to_str(int nb, char *s);
void			get_color_champions(t_gui *gui, unsigned char c);
void			get_list_pc(t_corewar *core, t_gui *gui);
int			get_magic(t_champions *champions, int fd);
int			little_to_big_endian(int nb);
int			get_size(t_champions *champions, int fd);
int			check_size_read(int size,
					t_champions *champions,
					int fd,
					int s_read);
void			swap_int(int *a, int *b);
void			sort_int(int *tab, int size);
void			attribute_one_def(t_champions *champions,
					  int place_after);
void			attribute_two_def(t_champions *champions,
					  int pa,
					  int nb);
void			attribute_three_def(t_champions *champions);
int			check_place_arena(unsigned char *info_arena,
					  unsigned int prog_number,
					  unsigned int *i);
int			load_players_name(t_corewar *core, t_gui *gui);
int			manage_event(t_corewar *core, t_gui *gui, int *pause);
void			get_cycle_to_wait(t_corewar *core,
					  t_champions *champions);
int			check_live_process(t_corewar *core,
					   unsigned int cycle_to_die_cur);
void			my_putnbr(int nb);
int			desassemble_it(t_corewar *core);

#endif /* !MACHINE_H_ */
