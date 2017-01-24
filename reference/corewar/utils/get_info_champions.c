/*
** load_champions_in_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 16:06:34 2014 chapui_s
** Last update Sat Apr 12 17:46:36 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../machine.h"
#include "../../op/op.h"

static int	get_name(t_champions *champions, int fd)
{
  char		*name;
  char		buf;
  int		s_read;
  int		i;
  int		j;

  if ((name = (char*)malloc(PROG_NAME_LENGTH + 1)) == NULL)
    return (my_putstr("error: malloc\n", 2));
  i = 0;
  j = 0;
  while (i < PROG_NAME_LENGTH && (s_read = read(fd, &buf, 1)) > 0)
  {
    if (buf != 0)
    {
      name[j] = buf;
      j += 1;
    }
    i += 1;
  }
  name[j] = 0;
  if (s_read == -1)
    return (my_putstr("error: read\n", 2));
  champions->name = name;
  return (0);
}

static int	get_comment(t_champions *champions, int fd)
{
  char		*comment;
  char		buf;
  int		s_read;
  int		i;
  int		j;

  if ((comment = (char*)malloc(COMMENT_LENGTH + 1)) == NULL)
    return (my_putstr("error: malloc\n", 2));
  i = 0;
  j = 0;
  while (i < COMMENT_LENGTH && (s_read = read(fd, &buf, 1)) > 0)
  {
    if (buf != 0)
    {
      comment[j] = buf;
      j += 1;
    }
    i += 1;
  }
  comment[j] = 0;
  if (s_read == -1)
    return (my_putstr("error: read\n", 2));
  champions->comment = comment;
  return (0);
}

int		get_name_comment_champions(t_champions *champions, int *fd)
{
  if ((*fd = open(champions->filename, O_RDONLY)) == -1)
    return (my_putstr("error: read\n", 2));
  if (get_magic(champions, *fd) == -1)
    return (-1);
  if ((lseek(*fd, sizeof(int), SEEK_SET)) == -1)
    return (my_putstr("error: lseek\n", 2));
  if ((get_name(champions, *fd)) == -1)
    return (-1);
  if ((lseek(*fd, (sizeof(int) + (PROG_NAME_LENGTH + 4)), SEEK_SET)) == -1)
    return (my_putstr("error: lseek\n", 2));
  if (get_size(champions, *fd) == -1)
    return (-1);
  if ((lseek(*fd, (sizeof(int) * 2) + PROG_NAME_LENGTH + 4, SEEK_SET)) == -1)
    return (my_putstr("error: lseek\n", 2));
  if ((get_comment(champions, *fd)) == -1)
    return (-1);
  if ((lseek(*fd, sizeof(struct header_s), SEEK_SET)) == -1)
      return (my_putstr("error: lseek\n", 2));
  return (0);
}
