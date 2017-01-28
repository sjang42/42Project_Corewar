/*
** arguments.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 16:29:06 2014 chapui_s
** Last update Sat Apr 12 17:38:13 2014 chapui_s
*/

#include "machine.h"

int		is_error_in_args(int argc, char **argv)
{
  int		i;

  i = 1;
  if (argc < 2)
    return (-1);
  while (i < argc)
  {
    if (is_options(argv[i]))
    {
      if ((is_numbers(argv[i + 1])) == -1 && my_strcmp(argv[i], "-d") != 0)
	return (-1);
      i += 2;
    }
    else
    {
      if (is_file_dot_cor(argv[i]) == -1)
	return (-1);
      i += 1;
    }
  }
  if (is_one_file_cor(argc, argv) == -1)
    return (-1);
  return (0);
}

int			save_champion(int i, char **argv, t_corewar *core)
{
  int			cur;
  unsigned int		prog_number;
  unsigned int		load_address;

  cur = i;
  i -= 1;
  prog_number = 0;
  load_address = 0;
  while (i > 0 && is_file_dot_cor(argv[i]) == -1)
  {
    if (!(my_strcmp(argv[i], "-n")))
      prog_number = my_unsigned_atoi(argv[i + 1]);
    if (!(my_strcmp(argv[i], "-a")))
      load_address = (my_unsigned_atoi(argv[i + 1]) % MEM_SIZE);
    i -= 1;
  }
  if ((push_champion(core,
		     argv[cur],
		     prog_number,
		     load_address)) == -1)
    return (-1);
  return (0);
}

int		save_args(int argc, char **argv, t_corewar *core)
{
  int		i;
  unsigned int	nb_cor;

  i = 1;
  nb_cor = 0;
  while (i < argc)
  {
    if (is_file_dot_cor(argv[i]) == 1 && ++nb_cor)
      if ((save_champion(i, argv, core)) == -1)
	return (-1);
    i += 1;
  }
  core->nb_champions = nb_cor;
  return (0);
}

void		get_dump(int argc, char **argv, t_corewar *core)
{
  int		i;

  i = 0;
  core->nbr_cycle_dump = 0;
  core->is_desassembler = 0;
  while (i < argc)
  {
    if (my_strcmp(argv[i], "-dump") == 0)
      core->nbr_cycle_dump = my_unsigned_atoi(argv[i + 1]);
    if (my_strcmp(argv[i], "-d") == 0)
      core->is_desassembler = 1;
    i += 1;
  }
}

int		get_args(int argc, char **argv, t_corewar *core)
{
  if (is_error_in_args(argc, argv) == -1)
    return (usage());
  get_dump(argc, argv, core);
  if ((save_args(argc, argv, core)) == -1)
    return (-1);
  if ((attribute_prog_number(core->champions,
			     core->nb_champions)) == -1)
    return (-1);
  if ((attribute_address(core->champions,
			 core->nb_champions)) == -1)
    return (-1);
  return (0);
}
