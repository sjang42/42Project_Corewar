/*
** my_puts.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 17:04:58 2014 chapui_s
** Last update Sat Apr 12 18:15:13 2014 chapui_s
*/

#include <unistd.h>

void		my_putchar(char c)
{
  write(1, &c, 1);
}

int		my_putstr(char *s, int fd)
{
  while (s && *s)
    write(fd, s++, 1);
  return ((fd == 2) ? (-1) : (0));
}

void		my_putnbr(int nb)
{
  long		big;

  big = nb;
  if (big < 0)
  {
    my_putchar('-');
    big = -big;
  }
  if (big >= 10)
    my_putnbr(big / 10);
  my_putchar((big % 10) + '0');
}
