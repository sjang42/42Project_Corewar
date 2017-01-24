/*
** my_aff.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 17:52:46 2014 chapui_s
** Last update Wed Apr  9 16:16:28 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

static int	get_size_nb(int nb)
{
  int		size;

  size = 1;
  while (nb / 10 > 0)
  {
    size += 1;
    nb /= 10;
  }
  return (size);
}

static int	my_pow(int nb, int pow)
{
  int		i;
  int		res;

  i = 2;
  res = nb;
  if (pow < 0)
    return (0);
  if (pow == 0)
    return (1);
  while (i <= pow)
  {
    res *= nb;
    i += 1;
  }
  return (res);
}

int		octal_to_decimal(int oct)
{
  int		dec;
  int		size;
  int		i;
  int		tmp;

  dec = 0;
  i = 0;
  size = get_size_nb(oct);
  if (oct <= 0)
    return (0);
  while (i < size)
  {
    tmp = oct / (my_pow(10, size - i - 1));
    dec += (tmp * my_pow(8, size - i - 1));
    oct -= (tmp * my_pow(10, size - i - 1));
    i += 1;
  }
  return (dec);
}

int		my_aff(t_corewar *core,
		       t_champions *champions,
		       t_instruction *instruction)
{
  int		value_to_print;

  (void)core;
  value_to_print = 0;
  if (is_good_register(instruction->params[0]) == 1)
    value_to_print = champions->reg[instruction->params[0]];
  my_putchar(octal_to_decimal(value_to_print));
  return (0);
}
