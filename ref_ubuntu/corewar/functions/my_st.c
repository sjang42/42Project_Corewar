/*
** my_st.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 18:45:40 2014 chapui_s
** Last update Thu Apr 10 01:48:40 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

int		my_st(t_corewar *core,
		      t_champions *champions,
		      t_instruction *instruction)
{
  int		value_to_store;
  int		index;

  value_to_store = 0;
  if (is_good_register(instruction->params[0]) == 1)
    value_to_store = champions->reg[instruction->params[0]];
  if (is_register(instruction->type, 2) == 1)
  {
    if (is_good_register(instruction->params[1]) == 1)
      champions->reg[instruction->params[1]] = value_to_store;
  }
  else if (is_indirect(instruction->type, 2) == 1)
  {
    index = champions->pc - 5 + (instruction->params[1] % IDX_MOD);
    write_arena_four(core, champions, value_to_store, index);
  }
  return (0);
}
