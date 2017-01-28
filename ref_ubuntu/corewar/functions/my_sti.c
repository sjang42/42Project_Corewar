/*
** my_sti.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 18:45:40 2014 chapui_s
** Last update Thu Apr 10 01:48:56 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

static int	get_value_to_store(t_corewar *core,
				   t_champions *champions,
				   t_instruction *instruction)
{
  int		value_to_store;

  (void)core;
  value_to_store = 0;
  if (is_register(instruction->type, 1) == 1)
  {
    if (is_good_register(instruction->params[0]) == 1)
    {
      value_to_store = champions->reg[instruction->params[0]];
    }
  }
  return (value_to_store);
}

static int	get_second_value(t_corewar *core,
				 t_champions *champions,
				 t_instruction *instruction)
{
  int		second_value;

  (void)core;
  second_value = 0;
  if (is_register(instruction->type, 2) == 1)
  {
    if (is_good_register(instruction->params[1]) == 1)
      second_value = champions->reg[instruction->params[1]];
  }
  else if (is_direct(instruction->type, 2) == 1)
  {
    second_value = instruction->params[1];
  }
  else if (is_indirect(instruction->type, 2) == 1)
  {
    second_value = instruction->params[1];
  }
  return (second_value);
}

static int	get_third_value(t_corewar *core,
				t_champions *champions,
				t_instruction *instruction)
{
  int		third_value;

  (void)core;
  third_value = 0;
  if (is_register(instruction->type, 3) == 1)
  {
    if (is_good_register(instruction->params[2]) == 1)
      third_value = champions->reg[instruction->params[2]];
  }
  else if (is_direct(instruction->type, 3) == 1)
  {
    third_value = instruction->params[2];
  }
  return (third_value);
}

int		my_sti(t_corewar *core,
		       t_champions *champions,
		       t_instruction *instruction)
{
  int		value_to_store;
  int		second_value;
  int		third_value;
  int		ptr;

  value_to_store = get_value_to_store(core, champions, instruction);
  second_value = get_second_value(core, champions, instruction);
  third_value = get_third_value(core, champions, instruction);
  ptr = champions->pc - 7 + (second_value % IDX_MOD) + (third_value % IDX_MOD);
  ptr = ptr % MEM_SIZE;
  if (ptr < 0)
    ptr = MEM_SIZE + ptr;
    write_arena_four(core, champions, value_to_store,
  		     (ptr % MEM_SIZE));
  champions->carry = (value_to_store) ? (0) : (1);
  return (0);
}
