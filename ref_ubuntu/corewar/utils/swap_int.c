/*
** swap_int.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Apr  9 21:40:30 2014 chapui_s
** Last update Wed Apr  9 21:40:58 2014 chapui_s
*/

void		swap_int(int *a, int *b)
{
  int		tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}
