/*
** get_magic.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 16:06:34 2014 chapui_s
** Last update Wed Apr  9 20:22:38 2014 chapui_s
*/

#include <unistd.h>
#include "../machine.h"
#include "../../op/op.h"

int		get_magic(t_champions *champions, int fd)
{
  int		buf;

  buf = 0;
  if (read(fd, &buf, sizeof(int)) == -1)
    return (my_putstr("error: read\n", 2));
  buf = little_to_big_endian(buf);
  if (buf != COREWAR_EXEC_MAGIC)
  {
    my_putstr("error: bad magic number with ", 2);
    my_putstr(champions->filename, 2);
    my_putstr("\n", 2);
    return (-1);
  }
  return (0);
}
