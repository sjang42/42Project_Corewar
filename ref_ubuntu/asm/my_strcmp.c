/*
** my_strcmp.c for strcmp in /home/chapui_s/rendu/Piscine-C-Jour_06/ex_05
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Oct  7 10:26:21 2013 chapui_s
** Last update Sat Apr 12 15:47:59 2014 poulet_a
*/

int	my_strcmp(char *s1, char *s2)
{
  return ((*s1 == *s2 && *s1) ? (my_strcmp(++s1, ++s2)) : (*s1 - *s2));
}
