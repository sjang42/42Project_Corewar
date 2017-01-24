/*
** my_or.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 21:20:28 2014 chapui_s
** Last update Mon Apr 28 01:09:47 2014 chapui_s
*/

#include "../machine.h"

static int	get_size_param(int type)
{
  int		size;

  size = 0;
  while (type & 0b11000000)
  {
    if ((type & 0b11000000) == 1)
      size += 1;
    if ((type & 0b11000000) == 0b10)
      size += 4;
    else
      size += 2;
    type = type << 2;
  }
  return (size + 1);
}

static int	get_value(t_corewar *core,
			  t_champions *champions,
			  t_instruction *instruction,
			  int param)
{
  int		value;

  value = 0;
  if (is_register(instruction->type, param) == 1)
  {
    if (is_good_register(instruction->params[param - 1]) == 1)
      value = champions->reg[instruction->params[param - 1]];
  }
  else if (is_direct(instruction->type, param) == 1)
    value = instruction->params[param - 1];
  else if (is_indirect(instruction->type, param) == 1)
    value = read_arena(core, (champions->pc - get_size_param(instruction->type)
			      + (instruction->params[param - 1]
				 % IDX_MOD)) % MEM_SIZE, 4);
  return (value);
}

int		my_or(t_corewar *core,
		      t_champions *champions,
		      t_instruction *instruction)
{
  int		value1;
  int		value2;

  (void)core;
  value1 = get_value(core, champions, instruction, 1);
  value2 = get_value(core, champions, instruction, 2);
  if (is_good_register(instruction->params[2]) == 1)
    champions->reg[instruction->params[2]] = value1 | value2;
  champions->carry = (value1 | value2) ? (0) : (1);
  return (0);
}
