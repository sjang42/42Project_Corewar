/*
** my_strchr.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Apr 11 21:36:32 2014 chapui_s
** Last update Fri Apr 11 21:36:39 2014 chapui_s
*/

#include <stdlib.h>

char		*my_strchr(char *s, int c)
{
  int		i;

  i = 0;
  while (s[i])
  {
    if (s[i] == c)
      return (s + i);
    i = i + 1;
  }
  return (NULL);
}
