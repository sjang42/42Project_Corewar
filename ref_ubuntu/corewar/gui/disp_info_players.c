/*
** disp_info_players.c for Corewar in /home/chapui_s/travaux/Corewar/VM/gui
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 25 00:20:38 2014 chapui_s
** Last update Sat Apr 12 17:49:31 2014 poulet_a
*/

#include <unistd.h>
#include "../machine.h"

int		disp_players(t_gui *gui)
{
  SDL_Rect	position;
  int		i;

  i = 0;
  position.x = 100;
  position.y = 730;
  while (gui->players[i])
  {
    if (SDL_BlitSurface(gui->players[i], NULL, gui->screen, &position) < 0)
      return (my_putstr("error :SDL_BlitSurface\n", 2));
    position.y += 15;
    i += 1;
  }
  return (0);
}

static int	disp_info_players_others(t_corewar *core,
					 t_gui *gui,
					 int cycles)
{
  SDL_Rect	position;
  char		str[50];

  gui->byte_arena = TTF_RenderText_Solid(gui->font_info,
					 int_to_str(cycles, &(str[0])),
					 gui->my_color);
  position.x = (WIN_X - 70);
  position.y = 745;
  if ((SDL_BlitSurface(gui->byte_arena, NULL, gui->screen, &position)) < 0)
    return (my_putstr("error :SDL_BlitSurface\n", 2));
  gui->byte_arena = TTF_RenderText_Solid(gui->font_info,
					 int_to_str(core->cycle_to_die_cur,
						    &(str[0])),
					 gui->my_color);
  position.x = (WIN_X - 70);
  position.y = 765;
  if ((SDL_BlitSurface(gui->byte_arena, NULL, gui->screen, &position)) < 0)
    return (my_putstr("error :SDL_BlitSurface\n", 2));
  if ((disp_players(gui)) == -1)
    return (-1);
  return (0);
}

int		disp_info_players(t_corewar *core,
				  t_gui *gui,
				  int cycles,
				  int pause)
{
  SDL_Rect	position;
  char		str[50];

  gui->my_color.r = 255;
  gui->my_color.g = 255;
  gui->my_color.b = 255;
  gui->byte_arena = TTF_RenderText_Solid(gui->font_info,
					 (pause == 0) ? ("PLAYING")
					 : ("PAUSED"),
					 gui->my_color);
  position.x = (WIN_X / 2) - (gui->byte_arena->w / 2);
  position.y = 710;
  if ((SDL_BlitSurface(gui->byte_arena, NULL, gui->screen, &position)) < 0)
    return (my_putstr("error :SDL_BlitSurface\n", 2));
  gui->byte_arena = TTF_RenderText_Solid(gui->font_info,
					 int_to_str(core->nb_champions,
						    &(str[0])),
					 gui->my_color);
  position.x = (WIN_X - 70);
  position.y = 725;
  if ((SDL_BlitSurface(gui->byte_arena, NULL, gui->screen, &position)) < 0)
    return (my_putstr("error :SDL_BlitSurface\n", 2));
  if ((disp_info_players_others(core, gui, cycles)) == -1)
    return (-1);
  return (0);
}
