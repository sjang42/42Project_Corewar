/*
** attribute_address.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 19:15:12 2014 chapui_s
** Last update Wed Apr  9 23:34:50 2014 chapui_s
*/

#include "../machine.h"
#include "../../op/op.h"

void		attribute_one_def(t_champions *champions,
				  int place_after)
{
  int		place_save;
  t_champions	*tmp;

  place_save = 0;
  tmp = champions;
  while (tmp)
  {
    if (tmp->load_address != 0)
      place_save = tmp->load_address;
    tmp = tmp->next;
  }
  tmp = champions;
  while (tmp)
  {
    if (tmp->load_address == 0)
    {
      tmp->load_address = (place_save + place_after) % MEM_SIZE;
      place_save = tmp->load_address;
    }
    tmp = tmp->next;
  }
}

void		attribute_two_def(t_champions *champions,
				  int pa,
				  int nb)
{
  t_champions	*tmp;
  int		p[2];
  int		i;

  i = 0;
  tmp = champions;
  while (tmp)
  {
    if (tmp->load_address != 0)
      p[i++] = tmp->load_address;
    tmp = tmp->next;
  }
  (p[1] < p[0]) ? (swap_int(&(p[0]), &(p[1]))) : (0);
  (p[1] - p[0] > (MEM_SIZE / 2)) ? (pa = p[0] + ((p[1] - p[0]) / nb))
    : (pa = p[1] + ((MEM_SIZE - (p[1] - p[0])) / nb));
  while (champions)
  {
    (pa < 0) ? (pa += MEM_SIZE) : (0);
    if (champions->load_address == 0)
    {
      champions->load_address = (pa % MEM_SIZE);
      (p[1] - p[0] < MEM_SIZE / 2) ? (pa += (pa - p[1])) : (pa += (pa - p[0]));
    }
    champions = champions->next;
  }
}

static int	get_max_diff(int *tab, int *max_diff)
{
  int		i;
  int		max_place;

  i = 0;
  *max_diff = 0;
  while (i < 2)
  {
    if (tab[i + 1] - tab[i] > *max_diff)
    {
      *max_diff = tab[i + 1] - tab[i];
      max_place = i;
    }
    i += 1;
  }
  if (*max_diff < MEM_SIZE - tab[2])
  {
    *max_diff = MEM_SIZE - tab[2];
    max_place = 2;
  }
  return (max_place);
}

void		attribute_three_def(t_champions *champions)
{
  t_champions	*tmp;
  int		place[3];
  int		i;
  int		place_max;
  int		max_diff;

  i = 0;
  tmp = champions;
  while (tmp)
  {
    if (tmp->load_address != 0)
      place[i++] = tmp->load_address;
    tmp = tmp->next;
  }
  sort_int(&(place[0]), 3);
  place_max = get_max_diff(&(place[0]), &max_diff);
  while (champions)
  {
    if (champions->load_address == 0)
      champions->load_address = place[place_max] + (max_diff / 2);
    champions = champions->next;
  }
}
