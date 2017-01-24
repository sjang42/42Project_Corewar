/*
** load_champions_in_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 16:06:34 2014 chapui_s
** Last update Sat Apr 12 17:48:06 2014 chapui_s
*/

#include <unistd.h>
#include "../machine.h"
#include "../../op/op.h"

int		check_size_read(int size,
				t_champions *champions,
				int fd,
				int s_read)
{
  if (s_read == -1)
    return (my_putstr("error: read\n", 2));
  if (!(champions))
    return (my_putstr("error while loading file\n", 2));
  if (size != champions->size)
  {
    my_putstr("error: size indicate in file different from true size\n", 2);
    my_putstr("\tMaybe the file is corrupt: ", 2);
    my_putstr(champions->filename, 2);
    my_putstr("\n", 2);
    close(fd);
    return (-1);
  }
  close(fd);
  return (0);
}

int		get_size(t_champions *champions, int fd)
{
  int		buf;

  buf = 0;
  if (read(fd, &buf, sizeof(int)) == -1)
    return (my_putstr("error: read\n", 2));
  buf = little_to_big_endian(buf);
  champions->size = buf;
  return (0);
}
