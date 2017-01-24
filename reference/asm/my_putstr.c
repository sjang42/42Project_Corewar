/*
** my_putstr.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:13:55 2014 chapui_s
** Last update Fri Apr 11 00:25:26 2014 chapui_s
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
