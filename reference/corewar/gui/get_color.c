/*
** get_color.c for Corewar in /home/chapui_s/travaux/Corewar/VM/gui
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 24 18:49:25 2014 chapui_s
** Last update Sat Apr 12 17:49:59 2014 poulet_a
*/

#include "../machine.h"

void		get_list_pc(t_corewar *core, t_gui *gui)
{
  t_champions	*tmp;
  int		i;

  tmp = core->champions;
  i = 0;
  while (tmp && i < (MAX_PC * 2) - 1)
  {
    gui->list_pc[i] = tmp->pc;
    gui->list_pc[i + 1] = tmp->color_gui;
    i += 2;
    tmp = tmp->next;
  }
}

void		get_color_champions(t_gui *gui,
				    unsigned char c)
{
  gui->my_color.r = 30;
  gui->my_color.g = 30;
  gui->my_color.b = 30;
  if (c == 0 || c > 4)
    return ;
  (c == 1) ? (gui->my_color.r = 0) : (0);
  (c == 1) ? (gui->my_color.g = 255) : (0);
  (c == 1) ? (gui->my_color.b = 0) : (0);
  (c == 2) ? (gui->my_color.r = 0) : (0);
  (c == 2) ? (gui->my_color.g = 0) : (0);
  (c == 2) ? (gui->my_color.b = 255) : (0);
  (c == 3) ? (gui->my_color.r = 255) : (0);
  (c == 3) ? (gui->my_color.g = 255) : (0);
  (c == 3) ? (gui->my_color.b = 0) : (0);
  (c == 4) ? (gui->my_color.r = 66) : (0);
  (c == 4) ? (gui->my_color.g = 0) : (0);
  (c == 4) ? (gui->my_color.b = 66) : (0);
}

static int	is_pc(t_corewar *core,
		      t_gui *gui,
		      int i)
{
  unsigned int	cur;
  unsigned int	j;
  int		*list;

  cur = 0;
  j = 0;
  list = gui->list_pc;
  while (j < core->nb_champions && cur < (MAX_PC * 2) - 1)
  {
    if (list[cur] == i)
    {
      get_color_champions(gui, list[cur + 1]);
      return (1);
    }
    j += 1;
    cur += 2;
  }
  return (0);
}

static int	set_color_with_pc(t_gui *gui,
				  t_corewar *core,
				  int i)
{
  SDL_Color	fg_color;
  char		str[3];

  fg_color.r = 0;
  fg_color.g = 0;
  fg_color.b = 0;
  fg_color.unused = 0;
  if (is_pc(core, gui, i) != 0)
    gui->byte_arena = TTF_RenderText_Shaded(gui->font,
					    hex_to_str(core->arena[i],
						       &str[0]),
					    fg_color,
					    gui->my_color);
  else
    gui->byte_arena = TTF_RenderText_Solid(gui->font,
  					   hex_to_str(core->arena[i],
						      &str[0]),
  					   gui->my_color);
  if (gui->byte_arena == NULL)
    return (my_putstr("error: TTF_RenderText\n", 2));
  return (0);
}

int		get_color(t_gui *gui,
			  t_corewar *core,
			  int i)
{
  get_color_champions(gui, core->info_arena[i]);
  if ((set_color_with_pc(gui, core, i)) == -1)
    return (-1);
  return (0);
}
