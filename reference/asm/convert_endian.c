/*
** convert_endian.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Apr 11 19:26:54 2014 chapui_s
** Last update Sat Apr 12 15:20:05 2014 poulet_a
*/

static int	is_little(void)
{
  char		a;

  a = 1;
  if (a >> 2 == 0)
    return (1);
  return (0);
}

static int	swap_two_octets(int nb)
{
  int		tmp;

  tmp = nb & 0xff;
  nb = (nb & 0xff00) / 0xff;
  nb = nb + (tmp * 0x100);
  return (nb);
}

int		little_to_big_endian(int nb)
{
  int		tmp;

  if (is_little() == 1)
  {
    tmp = nb & 0xffff;
    nb = (nb & 0xffff0000) / 0xffff;
    tmp = swap_two_octets(tmp) * 0x10000;
    nb = swap_two_octets(nb) + tmp;
  }
  return (nb);
}
