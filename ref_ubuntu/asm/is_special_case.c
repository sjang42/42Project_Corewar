/*
** is_special_case.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Apr 11 17:55:49 2014 chapui_s
** Last update Fri Apr 11 17:57:55 2014 chapui_s
*/

#include "asm.h"

int		is_special_case(char *instruction, int num)
{
  if ((my_strcmp(instruction, "sti") == 0 && (num == 2 || num == 3))
      || (my_strcmp(instruction, "ldi") == 0 && (num == 1 || num == 2))
      || (my_strcmp(instruction, "lldi") == 0 && (num == 1 || num == 2))
      || (my_strcmp(instruction, "zjmp") == 0))
    return (1);
  return (0);
}
