/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:49:02 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

void			init_bytes(unsigned char *bytes, int size)
{
  int			i;

  i = 0;
  while (i < size)
  {
    bytes[i] = 0;
    i += 1;
  }
}

static unsigned char	write_instruction(char *instruction, char *line)
{
  int			i;

  i = 0;
  while (op_tab[i].mnemonique
	 && my_strcmp(instruction, op_tab[i].mnemonique) != 0)
    i += 1;
  if (op_tab[i].code == 0)
  {
    my_putstr("bad instruction: '", 2);
    my_putstr(instruction, 2);
    my_putstr("' in line:\n\t'", 2);
    my_putstr(line, 2);
    my_putstr("'\n", 2);
  }
  return (op_tab[i].code);
}

static int		write_param(unsigned char *bytes,
				    char **tab,
				    int num,
				    int *index)
{
  if (tab[num][0] == 'r')
  {
    write_one_bytes(bytes, my_atoi(&(tab[num][1])), *index);
    *index = *index + 1;
  }
  else if (tab[num][0] != DIRECT_CHAR)
  {
    write_two_bytes(bytes, my_atoi(tab[num]), *index);
    *index = *index + 2;
  }
  else if (tab[num][0] == DIRECT_CHAR)
  {
    if (is_special_case(tab[0], num) == 1)
    {
      write_two_bytes(bytes, my_atoi(&(tab[num][1])), *index);
      *index = *index + 2;
    }
    else
    {
      write_four_bytes(bytes, my_atoi(&(tab[num][1])), *index);
      *index = *index + 4;
    }
  }
  return (0);
}

static void		write_bytes_desc(unsigned char *bytes,
					 char **tab,
					 char *type,
					 int *index)
{
  int			byte;

  if (my_strcmp(tab[0], "live") == 0 || my_strcmp(tab[0], "zjmp") == 0
      || my_strcmp(tab[0], "fork") == 0 || my_strcmp(tab[0], "lfork") == 0)
    return ;
  byte = 0;
  (type[0] == REG) ? (byte |= 0b01000000) : (0);
  (type[0] == IND) ? (byte |= 0b11000000) : (0);
  (type[0] == DIR) ? (byte |= 0b10000000) : (0);
  (tab[2] && type[1] == REG) ? (byte |= 0b00010000) : (0);
  (tab[2] && type[1] == IND) ? (byte |= 0b00110000) : (0);
  (tab[2] && type[1] == DIR) ? (byte |= 0b00100000) : (0);
  (tab[2] && tab[3] && type[2] == REG) ? (byte |= 0b00000100) : (0);
  (tab[2] && tab[3] && type[2] == IND) ? (byte |= 0b00001100) : (0);
  (tab[2] && tab[3] && type[2] == DIR) ? (byte |= 0b00001000) : (0);
  bytes[(*index)++] = byte;
}

int			write_bytes_code(t_file *file, unsigned char **bytes)
{
  int			i;
  int			param_cur;

  i = 0;
  if ((*bytes = (unsigned char*)malloc(get_max(file) + 1)) == NULL)
    return (my_putstr("error: malloc\n", 2));
  init_bytes(*bytes, get_max(file) + 1);
  while (file)
  {
    if (((*bytes)[i] = write_instruction(file->tab[0], file->line)) == 0)
      return (-1);
    i += 1;
    write_bytes_desc(*bytes, file->tab, file->type, &i);
    param_cur = 1;
    while (file->tab[param_cur])
    {
      write_param(*bytes, file->tab, param_cur, &i);
      param_cur += 1;
    }
    file = file->next;
  }
  return (0);
}
