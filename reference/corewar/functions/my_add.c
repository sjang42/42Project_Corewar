/*
** my_add.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 21:20:28 2014 chapui_s
** Last update Thu Apr 10 01:44:12 2014 chapui_s
*/

#include "../machine.h"

int		my_add(t_corewar *core,
		       t_champions *champions,
		       t_instruction *instruction)
{
  int		value1;
  int		value2;

  (void)core;
  value1 = 0;
  value2 = 0;
  if (is_good_register(instruction->params[0]) == 1)
    value1 = champions->reg[instruction->params[0]];
  if (is_good_register(instruction->params[1]) == 1)
    value2 = champions->reg[instruction->params[1]];
  if (is_good_register(instruction->params[2]) == 1)
    champions->reg[instruction->params[2]] = value1 + value2;
  champions->carry = (value1 + value2) ? (0) : (1);
  return (0);
}
