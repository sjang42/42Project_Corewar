/*
** is_type.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 21:35:33 2014 chapui_s
** Last update Sat Apr 12 15:50:40 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

int		is_label(char *str)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    i += 1;
  if (str[i - 1] == LABEL_CHAR)
    return (1);
  return (0);
}

int		is_param_label(char *str)
{
  if (str == NULL)
    return (-1);
  if (my_strlen(str) <= 2)
    return (-1);
  if (str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
    return (1);
  return (-1);
}

int		is_instruction(char *str)
{
  int		i;

  i = 0;
  while (op_tab[i].mnemonique
	 && my_strcmp(op_tab[i].mnemonique, str) != 0)
    i += 1;
  if (op_tab[i].mnemonique == NULL)
    return (-1);
  return (1);
}

int		get_type_param(t_file *file)
{
  int		i;
  int		cur;

  while (file)
  {
    cur = 0;
    i = 0;
    if (is_label(file->tab[0]) == 1)
      i = 1;
    i += 1;
    while (file->tab[i - 1] && file->tab[i])
    {
      if (is_register(file->tab[i]) == 1)
        file->type[cur] = REG;
      else if (is_direct(file->tab[i]) == 1)
        file->type[cur] = DIR;
      else if (is_indirect(file->tab[i]) == 1)
        file->type[cur] = IND;
      i += 1;
      cur += 1;
    }
    file->nb_args = cur;
    file = file->next;
  }
  return (0);
}
