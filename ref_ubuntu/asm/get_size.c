/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:50:33 2014 poulet_a
*/

#include "asm.h"

static int	is_special(char *instruction, int param_n)
{
  if ((my_strcmp(instruction, "sti") == 0 && (param_n == 2 || param_n == 3))
      || (my_strcmp(instruction, "ldi") == 0
	  && (param_n == 1 || param_n == 2))
      || (my_strcmp(instruction, "lldi") == 0
	  && (param_n == 1 || param_n == 2)))
    return (1);
  return (0);
}

static int	get_size_this_instruction_end(char **tab,
					      int i,
					      int size)
{
  int		instruction;
  int		param_n;

  instruction = i - 1;
  param_n = 1;
  while (tab[i])
  {
    if (tab[i][0] == 'r')
      size += 1;
    else if (tab[i][0] != DIRECT_CHAR)
      size += 2;
    else if (tab[i][0] == DIRECT_CHAR)
    {
      if (is_special(tab[instruction], param_n) == 1)
	size += 2;
      else
	size += 4;
    }
    param_n += 1;
    i += 1;
  }
  return (size);
}

static int	get_size_this_instruction(t_file *file,
					  char **tab,
					  int i,
					  int size)
{
  int		instruction;

  file->byte_n_before = size;
  instruction = i - 1;
  if (my_strcmp(tab[instruction], "zjmp") == 0
      || my_strcmp(tab[instruction], "fork") == 0
      || my_strcmp(tab[instruction], "lfork") == 0
      || my_strcmp(tab[instruction], "live") == 0)
  {
    if (my_strcmp(tab[instruction], "live") == 0)
      size += 5;
    else
      size += 3;
    file->byte_n_after = size;
    return (size);
  }
  size += 2;
  size = get_size_this_instruction_end(tab, i, size);
  file->byte_n_after = size;
  return (size);
}

int		get_size_each_instruction(t_file *file)
{
  int		size;
  int		i;

  size = 0;
  while (file)
  {
    i = 0;
    if (is_label(file->tab[0]) == 1)
    {
      file->byte_n_before = size;
      file->byte_n_after = size;
      i = 1;
    }
    if (file->tab[i] && is_instruction(file->tab[i]) == 1)
      size = get_size_this_instruction(file, file->tab, i + 1, size);
    file = file->next;
  }
  return (0);
}
