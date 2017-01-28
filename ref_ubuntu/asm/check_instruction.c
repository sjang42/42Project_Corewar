/*
** main.c for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:08:18 2014 chapui_s
** Last update Sat Apr 12 15:49:44 2014 poulet_a
*/

#include "asm.h"

static int	check_reg(char *param, char *line)
{
  int		i;
  int		reg;
  int		is_error;

  i = 1;
  is_error = 0;
  while (param[i])
  {
    if (param[i] < '0' || param[i] > '9')
      is_error += 1;
    i += 1;
  }
  reg = my_atoi(param + 1);
  if (reg == 0 || reg > REG_NUMBER)
    is_error += 1;
  if (is_error != 0)
  {
    my_putstr("error: bad register in line:\n\t'", 2);
    my_putstr(line, 2);
    my_putstr("'\n", 2);
    return (-1);
  }
  return (0);
}

static int	check_dir(char *param, char *line)
{
  int		i;
  int		is_error;

  (param[1] == '-') ? (i = 2) : (i = 1);
  is_error = 0;
  while (param[i])
  {
    if (param[i] < '0' || param[i] > '9')
      is_error += 1;
    i += 1;
  }
  if (is_error == 0 && my_strlen(param + 1) > 10)
  {
    my_putstr("warning: param direct too big at line:\n\t'", 1);
    my_putstr(line, 1);
    my_putstr("'\n", 1);
  }
  if (is_error != 0)
  {
    my_putstr("error: bad value in a direct param at line:\n\t'", 2);
    my_putstr(line, 2);
    my_putstr("'\n", 2);
    return (-1);
  }
  return (0);
}

static int	check_ind(char *param, char *line)
{
  int		i;
  int		is_error;

  is_error =0;
  (param[0] == '-') ? (i = 1) : (i = 0);
  while (param[i])
  {
    if (param[i] < '0' || param[i] > '9')
      is_error += 1;
    i += 1;
  }
  if (is_error == 0 && (my_atoi(param) > IDX_MOD || my_atoi(param) < IDX_MOD))
  {
    my_putstr("warning: indirect param > IDX_MOD at line:\n\t'", 1);
    my_putstr(line, 1);
    my_putstr("'\n", 1);
  }
  if (is_error != 0)
  {
    my_putstr("error: bad value in indirect param at line:\n\t'", 2);
    my_putstr(line, 2);
    my_putstr("'\n'", 2);
    return (-1);
  }
  return (0);
}

static int	check_good_type(char **tab, char *type, char *line)
{
  int		i;

  i = 0;
  while (tab[i] && tab[i + 1])
  {
    if (type[i] == REG
	&& check_reg(tab[i + 1], line) == -1)
      return (-1);
    if (type[i] == DIR
	&& check_dir(tab[i + 1], line) == -1)
      return (-1);
    if (type[i] == IND
	&& check_ind(tab[i + 1], line) == -1)
      return (-1);
    i += 1;
  }
  return (0);
}

int		check_instruction(t_file *file)
{
  int		i;

  while (file)
  {
    i = 0;
    while (op_tab[i].mnemonique
    	   && my_strcmp(op_tab[i].mnemonique, file->tab[0]) != 0)
      i += 1;
    if (op_tab[i].nbr_args == 0)
      return (bad_instruction(file->tab[0], file->line));
    if (op_tab[i].nbr_args != file->nb_args)
      return (bad_nb_args(file));
    if (check_good_type(file->tab, file->type, file->line) == -1)
      return (-1);
    file = file->next;
  }
  return (0);
}
