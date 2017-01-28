/*
** events.c for Corewar in /home/chapui_s/travaux/Corewar/VM/gui
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 00:54:12 2014 chapui_s
** Last update Sat Apr 12 17:49:49 2014 poulet_a
*/

#include "../machine.h"

int		manage_event(t_corewar *core,
			     t_gui *gui,
			     int *pause)
{
  SDL_Event	event;
  static int	is_dump;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
    {
      TTF_CloseFont(gui->font);
      SDL_Quit();
      TTF_Quit();
      return (-1);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
      *pause = !(*pause);
    else if (*pause != 0
	     && event.type == SDL_KEYDOWN
	     && event.key.keysym.sym == SDLK_d)
      is_dump += 1;
    else if (event.type == SDL_KEYDOWN)
      is_dump = 0;
    if (is_dump == 3)
      my_showmem(core->arena, MEM_SIZE);
  }
  return ((is_dump == 3) ? (-1) : (*pause));
}
