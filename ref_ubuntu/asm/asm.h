/*
** asm.h for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:14:52 2014 chapui_s
** Last update Sat Apr 12 15:43:08 2014 poulet_a
*/

#ifndef ASM_H_
# define ASM_H_

#include "../op/op.h"

typedef struct	s_file
{
  char		*line;
  char		**tab;
  char		type[3];
  int		nb_args;
  int		byte_n_before;
  int		byte_n_after;
  struct s_file	*prev;
  struct s_file	*next;
}		t_file;

# define REG	(1)
# define DIR	(2)
# define IND	(3)

int		my_putstr(char *s, int fd);
int		my_strlen(char *s);
int		push_file(t_file **file, char *line);
char		**my_str_to_wordtab(char *str);
int		is_label(char *str);
int		is_instruction(char *str);
int		my_strcmp(char *s1, char *s2);
int		get_size_each_instruction(t_file *file);
int		is_param_label(char *str);
char		*int_to_str(int nb);
int		resolve_label(t_file *file);
void		remove_bad_stuff(t_file **file);
int		my_atoi(char *str);
int		my_showmem(unsigned char *str, int size);
void		my_putchar(char c);
int		is_register(char *str);
int		is_indirect(char *str);
int		is_direct(char *str);
int		write_bytes_code(t_file *file, unsigned char **bytes);
int		get_max(t_file *file);
void		write_one_bytes(unsigned char *bytes, int to_write, int index);
void		write_two_bytes(unsigned char *bytes, int to_write, int index);
void		write_four_bytes(unsigned char *bytes, int to_write, int index);
int		get_type_param(t_file *file);
int		is_special_case(char *instruction, int num);
int		get_name_comment(t_file *file, char **name, char **comment);
int		little_to_big_endian(int nb);
int		get_header(header_t **header,
			   char *name,
			   char *comment,
			   int size);
void		free_list(t_file *list);
void		free_var(char *name,
			 char *comment,
			 header_t *header,
			 unsigned char *bytes);
char		*my_strchr(char *s, int c);
int		check_instruction(t_file *file);
int		bad_instruction(char *instruction, char *line);
int		bad_nb_args(t_file *file);
int		write_in_file(t_file *file,
			      unsigned char *bytes,
			      header_t *header,
			      char *filename);
int		read_file(char *filename, t_file **file);

#endif /* !ASM_H_ */
