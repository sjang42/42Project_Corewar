/*
** is_type.c for Corewar in /home/chapui_s/travaux/Corewar/VM/functions
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 28 18:02:49 2014 chapui_s
** Last update Fri Mar 28 21:19:18 2014 chapui_s
*/

#include "../machine.h"

int		is_direct(int octet_type, int num_param)
{
  int		i;

  i = 1;
  while (i < num_param)
  {
    octet_type = octet_type << 2;
    i += 1;
  }
  if ((octet_type & 0b11000000) == 0b10000000)
    return (1);
  return (0);
}

int		is_indirect(int octet_type, int num_param)
{
  int		i;

  i = 1;
  while (i < num_param)
  {
    octet_type = octet_type << 2;
    i += 1;
  }
  if ((octet_type & 0b11000000) == 0b11000000)
    return (1);
  return (0);
}

int		is_register(unsigned char octet_type, int num_param)
{
  int		i;

  i = 1;
  while (i < num_param)
  {
    octet_type = octet_type << 2;
    i += 1;
  }
  if ((octet_type & 0b11000000) == 0b01000000)
    return (1);
  return (0);
}
