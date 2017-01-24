/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:50:20 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

void		free_list(t_file *list)
{
  t_file	*tmp;
  int		i;

  while (list)
  {
    i = 0;
    tmp = list->next;
    free(list->line);
    while (list->tab[i])
      free(list->tab[i++]);
    free(list->tab[i]);
    free(list);
    list = tmp;
  }
}

void		free_var(char *name,
			 char *comment,
			 header_t *header,
			 unsigned char *bytes)
{
  free(name);
  free(comment);
  free(header);
  free(bytes);
}
