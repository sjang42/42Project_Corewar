/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:49:16 2014 poulet_a
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "asm.h"

static void	print_dorcor(char *new_filename, int i, int is_dot)
{
  (is_dot == 0) ? (i += 1) : (0);
  new_filename[i] = '.';
  new_filename[i + 1] = 'c';
  new_filename[i + 2] = 'o';
  new_filename[i + 3] = 'r';
  new_filename[i + 4] = 0;
}

static char	*get_new_filename(char *filename)
{
  char		*new_filename;
  int		is_dot;
  int		i;

  i = 0;
  is_dot = 0;
  while (filename[i + 1])
  {
    (filename[i] == '.') ? (is_dot = 1) : (0);
    i += 1;
  }
  while (is_dot == 1 && i > 0 && filename[i] != '.')
    i -= 1;
  if ((new_filename = (char*)malloc(i + 6)) == NULL)
  {
    my_putstr("error: malloc\n", 2);
    return (NULL);
  }
  print_dorcor(new_filename, i, is_dot);
  while (i >= 0)
  {
    new_filename[i] = filename[i];
    i -= 1;
  }
  return (new_filename);
}

int		write_in_file(t_file *file,
			      unsigned char *bytes,
			      header_t *header,
			      char *filename)
{
  char		*new_filename;
  int		size_file;
  int		fd;

  if ((new_filename = get_new_filename(filename)) == NULL)
    return (-1);
  size_file = get_max(file);
  if ((fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (my_putstr("error: open\n", 2));
  write(fd, header, sizeof(*header));
  write(fd, bytes, size_file);
  close(fd);
  my_putstr(" ---> ", 1);
  my_putstr(new_filename, 1);
  my_putstr(" <---\n", 1);
  free(new_filename);
  return (0);
}
