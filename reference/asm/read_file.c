/*
** read_file.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:48:27 2014 poulet_a
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "asm.h"
#include "get_next_line.h"

int		read_file(char *filename, t_file **file)
{
  int		fd;
  char		*str;

  *file = NULL;
  if ((fd = open(filename, O_RDONLY)) == -1)
    return (my_putstr("error: open\n", 2));
  while ((str = get_next_line(fd)))
  {
    if (push_file(file, str) == -1)
      return (-1);
  }
  close(fd);
  if (*file == NULL)
    return (my_putstr("error: file empty\n", 2));
  return (0);
}
