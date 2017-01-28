/*
** my_strlen.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 20:37:19 2014 chapui_s
** Last update Thu Apr 10 20:37:57 2014 chapui_s
*/

int		my_strlen(char *s)
{
  int		size;

  size = 0;
  while (s && s[size])
    size += 1;
  return (size);
}
