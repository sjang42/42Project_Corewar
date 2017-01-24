/*
** my_ld.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 17:52:46 2014 chapui_s
** Last update Wed Apr  2 17:01:33 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

int		my_ld(t_corewar *core,
		      t_champions *champions,
		      t_instruction *instruction)
{
  int		value_to_load;

  value_to_load = 0;
  if (is_indirect(instruction->type, 1) == 1)
    value_to_load = read_arena(core, champions->pc
  			       + (instruction->params[0] % IDX_MOD), 4);
  else if (is_direct(instruction->type, 1) == 1)
    value_to_load = instruction->params[0];
  if (is_good_register(instruction->params[1]) == 1)
    champions->reg[instruction->params[1]] = value_to_load;
  champions->carry = (value_to_load) ? (0) : (1);
  return (0);
}
