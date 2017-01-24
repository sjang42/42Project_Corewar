/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:49:09 2014 poulet_a
*/

#include "asm.h"

int		get_max(t_file *file)
{
  while (file->next)
    file = file->next;
  return (file->byte_n_after);
}

void		write_one_bytes(unsigned char *bytes,
				int to_write,
				int index)
{
  bytes[index] = to_write;
}

void		write_two_bytes(unsigned char *bytes,
				int to_write,
                                int index)
{
  bytes[index] = to_write >> 8;
  bytes[index + 1] = (to_write & 0b11111111);
}

void		write_four_bytes(unsigned char *bytes,
				 int to_write,
                                 int index)
{
  bytes[index] = (to_write >> 24);
  bytes[index + 1] =
    (to_write & 0b00000000111111110000000000000000) >> 16;
  bytes[index + 2] =
    (to_write & 0b00000000000000001111111100000000) >> 8;
  bytes[index + 3] = (to_write & 0b11111111);
}
