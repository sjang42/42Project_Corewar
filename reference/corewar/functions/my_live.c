/*
** my_live.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 17:28:36 2014 chapui_s
** Last update Sat Apr 12 17:12:38 2014 chapui_s
*/

#include "../machine.h"

static void	im_alive(char *name, int nb)
{
  my_putstr("le joueur ", 1);
  my_putnbr(nb);
  my_putstr("(", 1);
  my_putstr(name, 1);
  my_putstr(") est en vie\n", 1);
}

int		my_live(t_corewar *core,
			t_champions *champions,
			t_instruction *instruction)
{
  if ((int)(champions->color_gui) == instruction->params[0])
  {
    im_alive(champions->name, champions->color_gui);
    champions->last_live = 0;
    core->last_live_nb = champions->color_gui;
    core->last_live_name = champions->name;
    core->nbr_live_cur += 1;
  }
  return (0);
}
