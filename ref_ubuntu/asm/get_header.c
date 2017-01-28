/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:50:23 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static void	init_header(header_t *head)
{
  unsigned char	*tmp;
  int		size;
  int		i;

  i = 0;
  size = sizeof(*head);
  tmp = (unsigned char*)head;
  while (i < size)
    tmp[i++] = 0;
}

int		get_header(header_t **header,
			   char *name,
			   char *comment,
			   int size)
{
  int		i;
  header_t	*head;

  if ((*header = (header_t*)malloc(sizeof(*head))) == NULL)
    return (my_putstr("error: malloc\n", 2));
  head = *header;
  init_header(head);
  head->magic = little_to_big_endian(COREWAR_EXEC_MAGIC);
  head->prog_size = little_to_big_endian(size);
  i = 0;
  while (name[i++])
    head->prog_name[i - 1] = name[i - 1];
  while (i < PROG_NAME_LENGTH + 1)
    head->prog_name[i++] = 0;
  i = 0;
  while (comment[i++])
    head->comment[i - 1] = comment[i - 1];
  while (i < COMMENT_LENGTH + 1)
    head->comment[i++] = 0;
  return (0);
}
