/*
** hex_to_str.c for Corewar in /home/chapui_s/travaux/Corewar/VM/gui
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 24 16:31:07 2014 chapui_s
** Last update Fri Apr  4 16:18:12 2014 chapui_s
*/

static char	hex_to_char(unsigned char hex)
{
  char		base[] = "0123456789ABCDEF";

  if (hex < 16)
    return (base[hex]);
  return ('.');
}

char		*hex_to_str(unsigned char c, char *str)
{
  str[0] = hex_to_char(c >> 4);
  str[1] = hex_to_char(c & 0x0f);
  str[2] = 0;
  return (str);
}
