/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:50:55 2014 poulet_a
*/

#include "asm.h"

int		bad_nb_args(t_file *file)
{
  my_putstr("error: bad number of args in line:\n\t'", 2);
  my_putstr(file->line, 2);
  my_putstr("'\n", 2);
  return (-1);
}

int		bad_instruction(char *instruction, char *line)
{
  my_putstr("bad instruction: '", 2);
  my_putstr(instruction, 2);
  my_putstr("' in line:\n\t'", 2);
  my_putstr(line, 2);
  my_putstr("'\n", 2);
  return (-1);
}
