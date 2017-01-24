/*
** convert_endian.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Wed Apr  9 20:17:40 2014 chapui_s
** Last update Wed Apr  9 20:22:23 2014 chapui_s
*/

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

  tmp = nb & 0xffff;
  nb = (nb & 0xffff0000) / 0xffff;
  tmp = swap_two_octets(tmp) * 0x10000;
  nb = swap_two_octets(nb) + tmp;
  return (nb);
}
