/*
** is_good_register.c for Corewar in /home/chapui_s/travaux/Corewar/VM/exec_instructions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 18:54:18 2014 chapui_s
** Last update Thu Apr 10 16:48:22 2014 chapui_s
*/

#include "../../op/op.h"

int		is_good_register(int nb)
{
  return ((nb <= REG_NUMBER && nb > 0) ? (1) : (0));
}
