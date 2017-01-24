/*
** get_name_comment.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:50:27 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static int	bad_string(char *line)
{
  my_putstr("error: bad string\n\t", 2);
  my_putstr(line, 2);
  my_putstr("\n", 2);
  return (-1);
}

static int	get_string(char **string, char *line, int nc)
{
  int		i;

  i = my_strlen((nc == 1) ? (NAME_CMD_STRING) : (COMMENT_CMD_STRING));
  while (line[i] && (line[i] == ' ' || line[i] == '\t'))
    i += 1;
  if (line[i] == 0 || line[i] != '"')
    return (bad_string(line));
  i += 1;
  line = line + i;
  i = 0;
  while (line[i] && line[i] != '"')
    i += 1;
  if ((*string = (char*)malloc(i + 1)) == NULL)
    return (my_putstr("error: malloc\n", 2));
  i = 0;
  while (line[i] && line[i] != '"')
  {
    (*string)[i] = line[i];
    i += 1;
  }
  (*string)[i] = 0;
  while (line[++i])
    if (line[i] != '\t' && line[i] != ' ')
      return (bad_string(line));
  return (0);
}

static int	get_name(t_file *file, char **name)
{
  t_file	*tmp;

  tmp = file;
  while (tmp && my_strcmp(tmp->tab[0], NAME_CMD_STRING) != 0)
    tmp = tmp->next;
  if (tmp)
  {
    if ((get_string(name, tmp->line, 1)) == -1)
      return (-1);
  }
  else
  {
    if ((*name = (char*)malloc(1)) == NULL)
      return (-1);
    *name[0] = 0;
  }
  return (0);
}

static int	get_comment(t_file *file, char **comment)
{
  t_file	*tmp;

  tmp = file;
  while (tmp && my_strcmp(tmp->tab[0], COMMENT_CMD_STRING) != 0)
    tmp = tmp->next;
  if (tmp)
  {
    if ((get_string(comment, tmp->line, 2)) == -1)
      return (-1);
  }
  else
  {
    if ((*comment = (char*)malloc(1)) == NULL)
      return (-1);
    *comment[0] = 0;
  }
  return (0);
}

int		get_name_comment(t_file *file, char **name, char **comment)
{
  if ((get_name(file, name)) == -1)
    return (-1);
  if ((get_comment(file, comment)) == -1)
    return (-1);
  if (my_strlen(*name) > 0 || my_strlen(*comment) > 0)
  {
    my_putstr("name    :  '", 1);
    my_putstr(*name, 1);
    my_putstr("'\n", 1);
  }
  if (my_strlen(*comment) > 0)
  {
    my_putstr("comment :  '", 1);
    my_putstr(*comment, 1);
    my_putstr("'\n", 1);
  }
  return (0);
}
