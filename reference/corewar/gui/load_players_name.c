/*
** load_players_name.c for Corewar in /home/chapui_s/travaux/Corewar/VM/gui
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 24 16:31:07 2014 chapui_s
** Last update Sat Apr 12 17:50:12 2014 poulet_a
*/

#include <unistd.h>
#include "../machine.h"

int		load_players_name(t_corewar *core, t_gui *gui)
{
  t_champions	*tmp;
  unsigned int	cur;
  int		i;

  i = 0;
  cur = 1;
  tmp = core->champions;
  while (tmp)
  {
    if (tmp->prog_number == cur)
    {
      get_color_champions(gui, tmp->color_gui);
      if (my_strlen(tmp->name) > 0)
	if ((gui->players[i++] = TTF_RenderText_Solid(gui->font_info,
						      tmp->name,
						      gui->my_color)) == NULL)
	  return (my_putstr("error: TTF_RenderText\n", 2));
      cur += 1;
      tmp = core->champions;
    }
    else
      tmp = tmp->next;
  }
  gui->players[i] = NULL;
  return (0);
}
