/*
** read_write_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 18:57:53 2014 chapui_s
** Last update Thu Apr 10 00:38:05 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

static int	to_negativ(int nb, int nb_octet)
{
  int		i;
  int		tmp;
  int		res;

  res = 0;
  i = 0;
  if ((nb_octet == 4 && (nb & 0b1000000000000000000000000000000) != 0)
      || (nb_octet == 2 && (nb & 0b100000000000000) != 0))
  {
    if (nb_octet == 4)
      i = 0b1000000000000000000000000000000;
    else if (nb_octet == 2)
      i = 0b1000000000000000;
    while (i)
    {
      tmp = nb & i;
      if (tmp == 0)
	res += i;
      i = i >> 1;
    }
    res += 1;
    nb = -res;
  }
  return (nb);
}

int		read_arena(t_corewar *core, int index, int n_to_read)
{
  int		value;
  int		i;

  i = 0;
  value = 0;
  while (index < 0)
    index += MEM_SIZE;
  while (i < n_to_read)
  {
    value = value << 8;
    value += core->arena[(index + i) % MEM_SIZE];
    i += 1;
  }
  value = to_negativ(value, n_to_read);
  return ((n_to_read == 1 && (value > 16 || value < 1)) ? (16) : (value));
}

void		write_arena_two(t_corewar *core,
				t_champions *champions,
				int to_write,
				int index)
{
  core->arena[index % MEM_SIZE] = to_write >> 8;
  core->info_arena[index % MEM_SIZE] = champions->prog_number;
  core->arena[(index + 1) % MEM_SIZE] = (to_write & 0b11111111);
  core->info_arena[(index + 1) % MEM_SIZE] = champions->prog_number;
}

void		write_arena_four(t_corewar *core,
				 t_champions *champions,
				 int to_write,
				 int index)
{
  while (index < 0)
    index += MEM_SIZE;
  core->arena[index % MEM_SIZE] = (to_write >> 24);
  core->info_arena[index % MEM_SIZE] = champions->color_gui;
  core->arena[(index + 1) % MEM_SIZE] =
    (to_write & 0b00000000111111110000000000000000) >> 16;
  core->info_arena[(index + 1) % MEM_SIZE] = champions->color_gui;
  core->arena[(index + 2) % MEM_SIZE] =
    (to_write & 0b00000000000000001111111100000000) >> 8;
  core->info_arena[(index + 2) % MEM_SIZE] = champions->color_gui;
  core->arena[(index + 3) % MEM_SIZE] = (to_write & 0b11111111);
  core->info_arena[(index + 3) % MEM_SIZE] = champions->color_gui;
}
