/*
** my_atoi.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 19:58:06 2014 chapui_s
** Last update Thu Mar 20 19:59:53 2014 chapui_s
*/

unsigned int	my_unsigned_atoi(char *str)
{
  unsigned int	i;
  unsigned int	number;

  i = 0;
  number = 0;
  if (!(str))
    return (0);
  while (str[i] >= 48 && str[i] <= 57)
  {
    number *= 10;
    number += ((int)str[i] - 48);
    i++;
  }
  return (number);
}
