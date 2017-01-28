/*
** my_showmem.c for showmem in /home/chapui_s/rendu/Piscine-C-Jour_06/ex_18
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Oct  7 18:05:37 2013 chapui_s
** Last update Fri Apr 11 02:14:30 2014 chapui_s
*/

#include "asm.h"

void		my_put_hexa(unsigned char nb, char *base, int is_first)
{
  if (nb < 16 && is_first == 1)
    my_putchar('0');
  if (nb >= 16)
    my_put_hexa(nb / 16, base, 0);
  my_putchar(base[(nb % 16)]);
}

void		write_hex(int i, int line_cur, int size, unsigned char *str)
{
  while (i < (32 * line_cur + 32) && i < size)
  {
    my_put_hexa(str[i], "0123456789ABCDEF", 1);
    i = i + 1;
  }
}

int		my_showmem(unsigned char *str, int size)
{
  int		nb_lines;
  int		line_cur;
  int		i;

  line_cur = 0;
  i = 0;
  nb_lines = 1 + size / 32;
  while (line_cur < nb_lines && i < size)
  {
    write_hex(i, line_cur, size, str);
    my_putchar('\n');
    line_cur = line_cur + 1;
    i = 32 * line_cur;
  }
  return (0);
}
