/*
** get_img.c for  in /home/broggi_t/projets/corewar/VM/gui
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 12 16:27:35 2014 broggi_t
** Last update Sat Apr 12 16:27:35 2014 broggi_t
*/

#include <stdlib.h>
#include "../machine.h"

int	get_image_path(t_gui *gui, char *exec_path)
{
  int	i;
  char	*img;
  char	*ttf;

  i = my_strlen(exec_path) - 1;
  while (i >=0 && exec_path[i] != '/')
    --i;
  if ((img = malloc(sizeof(char) * (i + my_strlen("Corewar.bmp")))) == NULL ||
      (ttf = malloc(sizeof(char) * (i + my_strlen("arial.ttf")))) == NULL)
    return (-1);
  exec_path[i + 2] = 0;
  if ((img = my_strcat(exec_path, "Corewar.bmp")) == NULL ||
      (ttf = my_strcat(exec_path, "arial.ttf")) == NULL)
    return (-1);
  if ((gui->background = SDL_LoadBMP(img)) == NULL)
    return (my_putstr("error: SDL_LoadBMP\n", 2));
  if ((gui->font = TTF_OpenFont(ttf, 11)) == NULL ||
      (gui->font_info = TTF_OpenFont(ttf, 13)) == NULL)
    return (my_putstr("error: TTF_OpenFont\n", 2) | 1);
  return (0);
}
