/*
** my_strdup.c for  in /home/broggi_t/projets/corewar/VM/utils
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 12 16:56:44 2014 broggi_t
** Last update Sat Apr 12 16:56:44 2014 broggi_t
*/

#include <stdlib.h>
#include "../machine.h"

char	*my_strdup(char *s)
{
  char	*r;
  int	i;

  if (s == NULL || (r = malloc((my_strlen(s) + 1) * sizeof(char))) == NULL)
    return (NULL);
  i = -1;
  while (s[++i])
    r[i] = s[i];
  r[i] = 0;
  return (r);
}
