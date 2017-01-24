/*
** my_zjmp.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 31 19:37:23 2014 chapui_s
** Last update Tue Apr  8 17:45:38 2014 chapui_s
*/

#include "../../op/op.h"
#include "../machine.h"

int		my_zjmp(t_corewar *core,
			t_champions *champions,
			t_instruction *instruction)
{
  int		where_to_go;

  (void)core;
  if (champions->carry == 1)
  {
    where_to_go = (champions->pc - 3) + (instruction->params[0] % IDX_MOD);
    where_to_go = where_to_go % MEM_SIZE;
    while (where_to_go < 0)
      where_to_go += MEM_SIZE;
    champions->pc = where_to_go;
  }
  return (0);
}
