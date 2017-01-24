/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 18:24:10 2014 poulet_a
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "asm.h"
#include "get_next_line.h"

int		compile_it(char *filename)
{
  t_file	*file;
  char		*name;
  char		*comment;
  header_t	*header;
  unsigned char	*bytes;

  file = NULL;
  if (((read_file(filename, &file)) == -1)
      ||(get_name_comment(file, &name, &comment) == -1))
    return (-1);
  get_size_each_instruction(file);
  get_type_param(file);
  if ((resolve_label(file)) == -1)
    return (-1);
  remove_bad_stuff(&file);
  if ((check_instruction(file)) == -1
      ||(write_bytes_code(file, &bytes)) == -1
      ||(get_header(&header, name, comment, get_max(file))) == -1
      ||(write_in_file(file, bytes, header, filename)) == -1)
    return (-1);
  free_list(file);
  free_var(name, comment, header, bytes);
  return (0);
}

int		main(int argc, char **argv)
{
  int		i;

  i = 1;
  while (i < argc)
  {
    my_putstr(" [assembling ", 1);
    my_putstr(argv[i], 1);
    my_putstr("]\n", 1);
    if ((compile_it(argv[i])) == -1)
      return (-1);
    i += 1;
  }
  if (i == 1)
    {
      my_putstr("no input files\n", 2);
      return (1);
    }
  return (0);
}
