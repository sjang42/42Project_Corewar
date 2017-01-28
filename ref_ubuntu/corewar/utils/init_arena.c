/*
** init_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 15:46:53 2014 chapui_s
** Last update Sat Apr 12 16:38:17 2014 poulet_a
*/

void		init_arena(unsigned char *ptr, unsigned int size, int value)
{
  unsigned int	i;

  i = 0;
  while (i < size)
    ptr[i++] = value;
}
