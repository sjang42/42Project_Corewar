/*
** my_str_to_wordtab.c for strw in /home/chapui_s/rendu/Piscine-C-Jour_08/ex_04
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Wed Oct  9 11:32:12 2013 chapui_s
** Last update Sat Apr 12 15:47:49 2014 poulet_a
*/

#include <stdlib.h>
#include "asm.h"

static int	is_it_alpha(char c)
{
  if (c != ' ' && c != '\t' && c != SEPARATOR_CHAR)
    return (1);
  return (0);
}

static int	count_words(char *str)
{
  int		word;
  int		i;
  int		nb_words;

  nb_words = 0;
  i = 0;
  word = 0;
  while (str[i])
  {
    if (word == 0 && is_it_alpha(str[i]) == 1)
    {
      word = 1;
      nb_words = nb_words + 1;
    }
    if (word == 1 && is_it_alpha(str[i]) == 0)
      word = 0;
    i = i + 1;
  }
  return (nb_words);
}

static void	dup_n_car(char *new_str, char *str, int begin, int end)
{
  int		i;

  i = 0;
  while (begin <= end)
  {
    new_str[i] = str[begin];
    begin = begin + 1;
    i = i + 1;
  }
  new_str[i] = '\0';
}

static int	save_words(char **tab, char *str, int nb_words)
{
  int		i;
  int		begin;
  int		word_cur;

  word_cur = 0;
  i = 0;
  begin = 0;
  while (word_cur < nb_words)
  {
    while (str[i] && is_it_alpha(str[i]) == 0)
      i = i + 1;
    begin = i;
    while (str[i] && is_it_alpha(str[i]) == 1)
      i = i + 1;
    if ((tab[word_cur] = (char*)malloc(sizeof(char) * ((i - 1) - begin + 2)))
	== NULL)
      return (my_putstr("error: malloc\n", 2));
    dup_n_car(tab[word_cur], str, begin, i - 1);
    i = i + 1;
    word_cur = word_cur + 1;
  }
  return (0);
}

char		**my_str_to_wordtab(char *str)
{
  int		nb_words;
  char		**tab;

  nb_words = count_words(str);
  if ((tab = (char**)malloc(sizeof(char*) * (nb_words + 1))) == NULL)
  {
    my_putstr("error: malloc\n", 2);
    return (NULL);
  }
  if ((save_words(tab, str, nb_words)) == -1)
    return (NULL);
  tab[nb_words] = NULL;
  return (tab);
}
