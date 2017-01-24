/*
** attribute_address.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 19:15:12 2014 chapui_s
** Last update Wed Apr  9 23:38:26 2014 chapui_s
*/

#include "../machine.h"
#include "../../op/op.h"

static int	is_addr_already_define(t_champions *champions)
{
  int		defined;

  defined = 0;
  while (champions)
  {
    if (champions->load_address != 0)
      defined += 1;
    champions = champions->next;
  }
  return (defined);
}

static int	attribute_address_defined(t_champions *champions,
					  unsigned int nb_champions,
					  int place_after)
{
  int		nb_already_defined;

  nb_already_defined = is_addr_already_define(champions);
  if (nb_already_defined == 1)
    attribute_one_def(champions, place_after);
  if (nb_champions != 2 && nb_already_defined == 2)
    attribute_two_def(champions, place_after, nb_champions - 1);
  if (nb_champions != 3 && nb_already_defined == 3)
    attribute_three_def(champions);
  while (champions)
  {
    champions->pc = champions->load_address;
    champions = champions->next;
  }
  return (0);
}

int		attribute_address(t_champions *champions,
				  unsigned int nb_champions)
{
  unsigned int	cur;
  unsigned int	place_after;

  cur = 0;
  place_after = MEM_SIZE / nb_champions;
  if (is_addr_already_define(champions) == 0)
  {
    while (champions)
    {
      champions->load_address = cur;
      cur += place_after;
      champions = champions->next;
    }
  }
  else
    attribute_address_defined(champions, nb_champions, place_after);
  return (0);
}
