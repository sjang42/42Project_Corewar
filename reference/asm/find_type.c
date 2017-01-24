/*
** find_type.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Apr 11 01:02:39 2014 chapui_s
** Last update Sat Apr 12 15:50:13 2014 poulet_a
*/

#include "asm.h"

int		is_register(char *str)
{
  if (str[0] == 'r')
    return (1);
  return (0);
}

int		is_indirect(char *str)
{
  if (str[0] != DIRECT_CHAR && str[0] != 'r')
    return (1);
  return (0);
}

int		is_direct(char *str)
{
  if (str[0] == DIRECT_CHAR)
    return (1);
  return (0);
}
