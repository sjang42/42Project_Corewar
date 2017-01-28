/*
** my_fork.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Apr  2 16:38:53 2014 chapui_s
** Last update Sat Apr 12 16:38:59 2014 poulet_a
*/

#include <stdlib.h>
#include "../machine.h"

static int	*copy_reg(int *father)
{
  int		*new;
  int		i;

  if ((new = (int*)malloc(sizeof(*new) * (REG_NUMBER + 1))) == NULL)
  {
    my_putstr(ALLOC_FAILED, 2);
    return (NULL);
  }
  i = 1;
  while (i <= REG_NUMBER)
  {
    new[i] = father[i];
    i += 1;
  }
  return (new);
}

int		my_fork(t_corewar *core,
			t_champions *champions,
			t_instruction *instruction)
{
  int		new_pc;
  t_champions	*tmp;

  (instruction->params[0] == 0) ? (instruction->params[0] = 3) : (0);
  new_pc = (champions->pc - 3) + (instruction->params[0] % IDX_MOD);
  while (new_pc < 0)
    new_pc += MEM_SIZE;
  new_pc = new_pc % MEM_SIZE;
  if ((push_champion(core, champions->filename,
  		     champions->prog_number, new_pc)) == -1)
    return (-1);
  tmp = core->last_champions;
  tmp->name = champions->name;
  tmp->comment = champions->comment;
  tmp->prog_number = ++(core->prog_number_max);
  tmp->carry = champions->carry;
  tmp->last_live = 0;
  tmp->cycle_to_wait = 2;
  tmp->color_gui = champions->color_gui;
  tmp->pc = new_pc;
  if ((tmp->reg = copy_reg(champions->reg)) == NULL)
    return (-1);
  core->nb_champions += 1;
  return (0);
}
