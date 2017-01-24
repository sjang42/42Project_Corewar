/*
** sort_int.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Apr  9 23:12:43 2014 chapui_s
** Last update Wed Apr  9 23:14:07 2014 chapui_s
*/

void		sort_int(int *tab, int size)
{
  int		i;
  int		tmp;

  i = 0;
  while (i < size - 1)
  {
    if (tab[i] > tab[i + 1])
    {
      tmp = tab[i];
      tab[i] = tab[i + 1];
      tab[i + 1] = tmp;
      i = 0;
    }
    i += 1;
  }
}
