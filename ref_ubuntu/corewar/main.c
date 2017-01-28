/*
** main.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 14:45:46 2014 chapui_s
** Last update Sat Apr 12 18:38:13 2014 chapui_s
*/

#include <stdlib.h>
#include "machine.h"

int		main(int argc, char **argv)
{
  t_corewar	core;

  core.champions = NULL;
  if ((get_args(argc, argv, &core)) == -1)
    return (-1);
  if ((load_arena(&core)) == -1)
    return (-1);
  if (core.is_desassembler == 1)
    return (desassemble_it(&core));
  if ((my_gui(&core, argv[0])) == -1)
    return (-1);
  return (0);
}
