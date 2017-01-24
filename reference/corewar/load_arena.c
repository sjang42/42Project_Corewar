/*
** load_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 15:35:36 2014 chapui_s
** Last update Sat Apr 12 18:34:20 2014 chapui_s
*/

#include <stdlib.h>
#include "machine.h"

int		load_arena(t_corewar *core)
{
  core->nbr_live_cur = 0;
  core->cycle_to_die_cur = CYCLE_TO_DIE;
  if ((core->arena = (unsigned char*)malloc(MEM_SIZE)) == NULL)
    return (my_putstr(ALLOC_FAILED, 2));
  if ((core->info_arena = (unsigned char*)malloc(MEM_SIZE)) == NULL)
    return (my_putstr(ALLOC_FAILED, 2));
  init_arena(core->arena, MEM_SIZE, 0);
  init_arena(core->info_arena, MEM_SIZE, 0);
  if ((load_champions_in_arena(core->arena, core->info_arena, core)) == -1)
    return (-1);
  return (0);
}
