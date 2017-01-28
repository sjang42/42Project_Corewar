/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 16:24:21 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static char	*get_new_label(char *label)
{
  char		*new_label;
  int		i;

  if ((new_label = (char*)malloc(my_strlen(label) + 2)) == NULL)
  {
    my_putstr("error: malloc\n", 2);
    return (NULL);
  }
  i = 2;
  while (label[i])
  {
    new_label[i - 2] = label[i];
    i += 1;
  }
  new_label[i - 2] = LABEL_CHAR;
  new_label[i - 1] = 0;
  return (new_label);
}

static char	*find_label(t_file *file,
			    char *label,
			    int index_cur,
			    char *line)
{
  char		*new_label;

  if ((new_label = get_new_label(label)) == NULL)
    return (NULL);
  while (file)
  {
    if (my_strcmp(file->tab[0], new_label) == 0)
    {
      free(label);
      free(new_label);
      return (int_to_str(file->byte_n_before - index_cur));
    }
    file = file->next;
  }
  my_putstr("error: cannot find label '", 2);
  my_putstr(label, 2);
  my_putstr("' in line:\n\t'", 2);
  my_putstr(line, 2);
  my_putstr("'\n", 2);
  free(label);
  free(new_label);
  return (NULL);
}

static int	is_good_label_chars(char *label)
{
  int		i;

  i = 0;
  while (label[i + 1])
  {
    if (my_strchr(LABEL_CHARS, label[i]) == NULL)
    {
      my_putstr("error: bad label char in '", 2);
      my_putstr(label, 2);
      my_putstr("'\n", 2);
      return (-1);
    }
    i += 1;
  }
  return (0);
}

static int	is_two_same_label(t_file *file)
{
  t_file	*tmp;

  while (file)
  {
    tmp = file->next;
    if (is_label(file->tab[0]))
    {
      if (is_good_label_chars(file->tab[0]) == -1)
	return (-1);
      while (tmp)
      {
      	if (is_label(tmp->tab[0])
	    && my_strcmp(file->tab[0], tmp->tab[0]) == 0)
      	{
	  my_putstr("error: this label defined more than one time: '", 2);
	  my_putstr(tmp->tab[0], 2);
	  my_putstr("'\n", 2);
	  return (-1);
	}
	tmp = tmp->next;
      }
    }
    file = file->next;
  }
  return (0);
}

int		resolve_label(t_file *file)
{
  t_file	*tmp;
  int		i;

  tmp = file;
  if (is_two_same_label(file) == -1)
    return (-1);
  while (tmp)
  {
    i = 0;
    while (tmp->tab[i])
    {
      if (is_param_label(tmp->tab[i]) == 1)
      	if ((tmp->tab[i] = find_label(file, tmp->tab[i],
				      tmp->byte_n_before, tmp->line)) == NULL)
	  return (-1);
      i += 1;
    }
    tmp = tmp->next;
  }
  return (0);
}
