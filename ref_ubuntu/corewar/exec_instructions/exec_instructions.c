/*
** exec_instructions.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 25 15:13:41 2014 chapui_s
** Last update Sat Apr 12 18:35:14 2014 chapui_s
*/

#include "../machine.h"

t_functions	tab_func[] =
{
  {1, my_live},
  {2, my_ld},
  {3, my_st},
  {4, my_add},
  {5, my_sub},
  {6, my_and},
  {7, my_or},
  {8, my_xor},
  {9, my_zjmp},
  {10, my_ldi},
  {11, my_sti},
  {12, my_fork},
  {13, my_lld},
  {14, my_lldi},
  {15, my_lfork},
  {16, my_aff},
};

static int	exec_function(t_corewar *core,
			      t_champions *champions,
			      t_instruction *instruction)
{
  if (instruction->code <= REG_NUMBER && instruction->code > 0)
  {
    if ((tab_func[instruction->code - 1].function(core,
						  champions,
						  instruction)) == -1)
      return (-1);
  }
  return (0);
}

void		get_cycle_to_wait(t_corewar *core, t_champions *champions)
{
  int		index;

  index = champions->pc % MEM_SIZE;
  while (index < 0)
    index = index + MEM_SIZE;
  index = index % MEM_SIZE;
  if (core->arena[index] >= 1 && core->arena[index] <= 16)
    champions->cycle_to_wait = op_tab[core->arena[index] - 1].nbr_cycles;
  else
    champions->cycle_to_wait = 0;
}

int		exec_instructions(t_corewar *core, t_champions *champions)
{
  t_instruction	instruction;
  t_champions	*tmp;

  tmp = champions;
  while (tmp)
  {
    if (tmp->cycle_to_wait <= 1)
    {
      get_instruction(core, tmp, &instruction);
      if ((exec_function(core, tmp, &instruction)) == -1)
	return (-1);
      get_cycle_to_wait(core, tmp);
    }
    else
      tmp->cycle_to_wait -= 1;
    tmp->last_live += 1;
    if (tmp == tmp->next)
      return (0);
    tmp = tmp->next;
  }
  return (0);
}

int			manage_instructions(t_corewar *core)
{
  static unsigned int	i;
  static unsigned int	cycle_to_die_cur;

  if (i == 0)
    i = 1;
  if (cycle_to_die_cur == 0)
    cycle_to_die_cur = CYCLE_TO_DIE;
  if (i >= cycle_to_die_cur)
  {
    if ((check_live_process(core, cycle_to_die_cur)) == 1)
      return (1);
    i = 1;
  }
  if (core->nbr_live_cur >= NBR_LIVE)
  {
    cycle_to_die_cur -= CYCLE_DELTA;
    core->cycle_to_die_cur = cycle_to_die_cur;
    core->nbr_live_cur = 0;
  }
  if ((exec_instructions(core, core->champions)) == -1)
    return (-1);
  i += 1;
  return (0);
}
