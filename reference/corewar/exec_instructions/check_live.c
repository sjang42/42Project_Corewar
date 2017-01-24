/*
** check_live.c for Corewar in /home/chapui_s/travaux/Corewar/VM/exec
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Apr 12 15:53:48 2014 chapui_s
** Last update Sat Apr 12 16:31:26 2014 poulet_a
*/

#include "../machine.h"

static void	winner(t_corewar *core)
{
  my_putstr("le joueur ", 1);
  if (core->champions)
    my_putnbr(core->champions->color_gui);
  else
    my_putnbr(core->last_live_nb);
  my_putstr("(", 1);
  if (core->champions)
    my_putstr(core->champions->name, 1);
  else
    my_putstr(core->last_live_name, 1);
  my_putstr(") a gagne\n", 1);
}

static int	search_who_still_alive(t_corewar *core)
{
  t_champions	*tmp;
  int		id_champion;

  tmp = core->champions;
  id_champion = 0;
  while (tmp)
  {
    if (id_champion != 0 && id_champion != tmp->color_gui)
      return (1);
    else
      id_champion = tmp->color_gui;
    tmp = tmp->next;
  }
  winner(core);
  return (0);
}

void		check_first_in_list(t_corewar *core,
				    unsigned int cycle_to_die_cur)
{
  t_champions	*tmp;

  tmp = core->champions;
  while (tmp && tmp->last_live >= cycle_to_die_cur)
  {
    core->champions = tmp->next;
    free(tmp->reg);
    free(tmp);
    core->nb_champions = core->nb_champions - 1;
    tmp = core->champions;
  }
}

int		check_live_process(t_corewar *core,
				   unsigned int cycle_to_die_cur)
{
  t_champions	*tmp;
  t_champions	*tmp_to_rm;

  check_first_in_list(core, cycle_to_die_cur);
  tmp = core->champions;
  while (tmp)
  {
    if (tmp->next && tmp->next->last_live >= cycle_to_die_cur)
    {
      tmp_to_rm = tmp->next;
      tmp->next = tmp->next->next;
      if (tmp->next == NULL)
	core->last_champions = tmp;
      free(tmp_to_rm->reg);
      free(tmp_to_rm);
      core->nb_champions = core->nb_champions - 1;
    }
    else
     tmp = tmp->next;
  }
  if ((search_who_still_alive(core)) == 0)
    return (1);
  return (0);
}
