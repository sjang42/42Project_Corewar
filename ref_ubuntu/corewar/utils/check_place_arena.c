/*
** check_place_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 00:04:19 2014 chapui_s
** Last update Thu Apr 10 00:11:03 2014 chapui_s
*/

#include "../machine.h"

int		check_place_arena(unsigned char *info_arena,
				  unsigned int prog_number,
				  unsigned int *i)
{
  if (info_arena[*i] == 0)
  {
    info_arena[*i] = prog_number;
    *i = *i + 1;
  }
  else
  {
    my_putstr("error: two champions are in the same address\n", 2);
    return (-1);
  }
  return (0);
}
