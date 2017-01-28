/*
** my_strcat.c for  in /home/broggi_t/projets/corewar/VM/utils
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 12 16:36:08 2014 broggi_t
** Last update Sat Apr 12 16:36:08 2014 broggi_t
*/

#include <stdlib.h>
#include "../machine.h"

char	*my_strcat(char *s1, char *s2)
{
  char	*r;
  int	i;
  int	j;

  if (s1 == NULL || s2 == NULL)
    return (NULL);
  if ((r = malloc((my_strlen(s1) + my_strlen(s2) + 1) * sizeof(char))) == NULL)
    return (NULL);
  i = -1;
  while (s1[++i])
    r[i] = s1[i];
  j = -1;
  --i;
  while (s2[++j])
    r[i++] = s2[j];
  r[i] = 0;
  return (r);
}
