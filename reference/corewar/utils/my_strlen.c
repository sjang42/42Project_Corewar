/*
** my_strlen.c for Corewar in /home/chapui_s/travaux/Corewar/VM/utils
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 25 00:14:57 2014 chapui_s
** Last update Tue Mar 25 00:16:19 2014 chapui_s
*/

int		my_strlen(char *s)
{
  int		size;

  size = 0;
  while (s && *s && s++)
    size += 1;
  return (size);
}
