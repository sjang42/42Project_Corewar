/*
** is_numbers.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 18:19:21 2014 chapui_s
** Last update Sat Apr 12 17:34:21 2014 chapui_s
*/

#include "../machine.h"

int		is_numbers(char *s)
{
  if (!(s))
    return (-1);
  while (s && *s)
  {
    if (*s < '0' || *s > '9')
      return (-1);
    s += 1;
  }
  return (0);
}

int		is_options(char *s)
{
  if (!(my_strcmp(s, "-dump"))
      || !(my_strcmp(s, "-n"))
      || !(my_strcmp(s, "-a"))
      || !(my_strcmp(s, "-d")))
  {
    return (1);
  }
  else
  {
    return (0);
  }
}

int		is_file_dot_cor(char *s)
{
  unsigned int	i;

  i = 0;
  while (s && s[i])
    i += 1;
  if (i < 5)
  {
    return (-1);
  }
  i = i - 4;
  if (my_strcmp(s + i, ".cor") != 0)
  {
    return (-1);
  }
  else
  {
    return (1);
  }
}

int		is_one_file_cor(int argc, char **argv)
{
  unsigned int	nb_cor;
  int		i;

  i = 1;
  nb_cor = 0;
  while (i < argc)
  {
    if (is_file_dot_cor(argv[i]) == 1)
    {
      nb_cor += 1;
    }
    i += 1;
  }
  return ((nb_cor > 0) ? (0) : (-1));
}
