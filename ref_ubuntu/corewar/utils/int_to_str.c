/*
** int_to_str.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Apr  5 16:22:30 2014 chapui_s
** Last update Sat Apr  5 16:53:50 2014 chapui_s
*/

static int	get_size_nb(int nb)
{
  int		size;

  size = 1;
  nb = (nb < 0) ? (-nb) : (nb);
  while (nb >= 10)
  {
    size *= 10;
    nb = nb / 10;
  }
  return (size);
}

char		*int_to_str(int nb, char *s)
{
  int		size;
  int		i;

  i = 0;
  size = get_size_nb(nb);
  while (size > 0)
  {
    s[i] = (nb / size) + '0';
    nb -= ((nb / size) * size);
    size /= 10;
    i += 1;
  }
  s[i] = 0;
  return (s);
}
