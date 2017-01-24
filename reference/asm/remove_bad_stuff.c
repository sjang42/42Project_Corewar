/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:48:40 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static void	remove_very_bad_stuff(t_file *file)
{
  int		i;

  while (file)
  {
    if (is_label(file->tab[0]) == 1)
    {
      i = 0;
      while (file->tab[i])
      {
	file->tab[i] = file->tab[i + 1];
	i += 1;
      }
      free(file->tab[i]);
    }
    file = file->next;
  }
}

static int	is_bad_stuff(char **tab)
{
  if (my_strcmp(tab[0], ".name") == 0
      || my_strcmp(tab[0], ".comment") == 0
      || (is_label(tab[0]) == 1 && tab[1] == NULL))
    return (1);
  return (0);
}

static void	remove_first_bad_stuff(t_file **file)
{
  t_file	*tmp;
  int		i;

  tmp = *file;
  while (tmp && is_bad_stuff(tmp->tab) == 1)
  {
    i = 0;
    *file = tmp->next;
    free(tmp->line);
    while (tmp->tab[i])
    {
      free(tmp->tab[i]);
      i += 1;
    }
    free(tmp->tab[i]);
    free(tmp);
    tmp = *file;
  }
}

void		remove_bad_stuff(t_file **file)
{
  t_file	*tmp;
  t_file	*tmp_to_rm;
  int		i;

  remove_first_bad_stuff(file);
  tmp = *file;
  while (tmp)
  {
    if (tmp->next && is_bad_stuff(tmp->next->tab) == 1)
    {
      i = 0;
      tmp_to_rm = tmp->next;
      tmp->next = tmp->next->next;
      free(tmp_to_rm->line);
      while (tmp_to_rm->tab[i])
	free(tmp_to_rm->tab[i++]);
      free(tmp_to_rm->tab[i]);
      free(tmp_to_rm);
    }
    else
      tmp = tmp->next;
  }
  remove_very_bad_stuff(*file);
}
