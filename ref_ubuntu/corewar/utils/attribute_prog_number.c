/*
** attribute_prog_number.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 20:21:19 2014 chapui_s
** Last update Wed Apr  2 18:09:24 2014 chapui_s
*/

#include "../machine.h"

static void	attribute_i_to_someone(t_champions *list_champion,
				       unsigned int i)
{
  t_champions	*tmp;
  unsigned int	is_already_attr;

  tmp = list_champion;
  is_already_attr = 0;
  while (tmp)
  {
    if (tmp->prog_number == i)
      is_already_attr = 1;
    tmp = tmp->next;
  }
  if (is_already_attr == 1)
    return ;
  tmp = list_champion;
  while (tmp)
  {
    if (tmp->prog_number == 0)
    {
      tmp->prog_number = i;
      return ;
    }
    tmp = tmp->next;
  }
}

static int	check_same_prog_number(t_champions *list_champion)
{
  t_champions	*tmp;
  t_champions	*tmp2;

  tmp = list_champion;
  while (tmp)
  {
    tmp2 = tmp->next;
    while (tmp2)
    {
      if (tmp->prog_number == tmp2->prog_number && tmp->prog_number != 0)
	return (my_putstr("error: two programs have the same number\n", 2));
      tmp2 = tmp2->next;
    }
    tmp = tmp->next;
  }
  return (0);
}

static int	check_big_prog_number(t_champions *list_champion,
				      unsigned int nb_champions)
{
  t_champions	*tmp;

  tmp = list_champion;
  while (tmp)
  {
    if (tmp->prog_number > nb_champions)
      return (my_putstr("error: prog_number too big\n", 2));
    tmp = tmp->next;
  }
  return (0);
}

int		attribute_prog_number(t_champions *list_champion,
				      unsigned int nb_champions)
{
  unsigned int	i;

  i = 1;
  if ((check_same_prog_number(list_champion)) == -1)
    return (-1);
  if ((check_big_prog_number(list_champion, nb_champions)) == -1)
    return (-1);
  while (i <= nb_champions)
  {
    attribute_i_to_someone(list_champion, i);
    i += 1;
  }
  while (list_champion)
  {
    list_champion->color_gui = list_champion->prog_number;
    list_champion = list_champion->next;
  }
  return (0);
}
