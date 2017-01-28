/*
** list_file.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:35:14 2014 chapui_s
** Last update Sat Apr 12 15:50:45 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static t_file	*create_file(char *line)
{
  t_file	*new;

  if ((new = (t_file*)malloc(sizeof(*new))))
  {
    new->line = line;
    if ((new->tab = my_str_to_wordtab(line)) == NULL)
      return (NULL);
    new->byte_n_before = 0;
    new->byte_n_after = 0;
    new->nb_args = 0;
    new->type[0] = 0;
    new->type[1] = 0;
    new->type[2] = 0;
    new->next = NULL;
  }
  else
    my_putstr("error: malloc\n", 2);
  return (new);
}

static int	is_only_space(char *str)
{
  int		i;

  i = 0;
  while (str[i])
  {
    if (str[i] != ' ' && str[i] != '\t')
      return (0);
    i += 1;
  }
  return (1);
}

static void	remove_comment(char *str)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str[i])
  {
    j = i;
    if (str[i] == COMMENT_CHAR || str[i] == ';')
      while (str[j])
	str[j++] = 0;
    i += 1;
  }
}

int		push_file(t_file **file, char *line)
{
  t_file	*tmp;

  remove_comment(line);
  if (my_strlen(line) == 0 || is_only_space(line) == 1)
  {
    free(line);
    return (0);
  }
  tmp = *file;
  if (tmp)
  {
    while (tmp->next)
      tmp = tmp->next;
    if ((tmp->next = create_file(line)) == NULL)
      return (-1);
  }
  else
    if ((*file = create_file(line)) == NULL)
      return (-1);
  return (0);
}
