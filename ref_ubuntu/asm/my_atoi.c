/*
** my_atoi.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 19:58:06 2014 chapui_s
** Last update Fri Apr 11 00:36:12 2014 chapui_s
*/

int		my_atoi(char *str)
{
  unsigned int	i;
  int		number;
  int		neg;

  i = 0;
  number = 0;
  if (!(str))
    return (0);
  neg = 0;
  if (str[0] == '-')
  {
    i = 1;
    neg = 1;
  }
  while (str[i] >= 48 && str[i] <= 57)
  {
    number *= 10;
    number += ((int)str[i] - 48);
    i++;
  }
  if (neg == 1)
    number = -number;
  return (number);
}
