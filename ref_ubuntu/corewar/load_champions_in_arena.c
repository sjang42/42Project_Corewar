/*
** load_champions_in_arena.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Fri Mar 21 16:06:34 2014 chapui_s
** Last update Sat Apr 12 17:52:30 2014 chapui_s
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "machine.h"

static int		load_file_in_arena(unsigned char *arena,
					   unsigned char *info_arena,
					   t_champions *champions)
{
  int			fd;
  int			s_read;
  char			buf;
  unsigned int		i;
  int			size;

  while (champions)
  {
    size = 0;
    i = champions->load_address;
    if (get_name_comment_champions(champions, &fd) == -1)
      return (-1);
    while ((s_read = read(fd, &buf, 1)) > 0 && ++size)
    {
      arena[i] = buf;
      if (check_place_arena(info_arena, champions->prog_number, &i) == -1)
	return (-1);
      (i == MEM_SIZE - 1) ? (i = 0) : (0);
    }
    if ((check_size_read(size, champions, fd, s_read)) == -1)
      return (-1);
    champions = champions->next;
  }
  return (0);
}

static void		init_reg(int *reg, unsigned prog_number)
{
  unsigned int		i;

  i = 2;
  reg[1] = (int)prog_number;
  while (i <= REG_NUMBER)
  {
    reg[i] = 0;
    i += 1;
  }
}

static int		init_values_champions(t_champions *champions)
{
  while (champions)
  {
    if ((champions->reg = (int*)malloc(sizeof(int) * (REG_NUMBER + 1)))
	== NULL)
      return (my_putstr(ALLOC_FAILED, 2));
    init_reg(champions->reg, champions->prog_number);
    champions->pc = champions->load_address;
    champions->carry = 0;
    champions->last_live = 0;
    champions->cycle_to_wait = 0;
    champions = champions->next;
  }
  return (0);
}

static int		find_max_prog_number(t_champions *champions)
{
  unsigned int		max;

  max = 0;
  while (champions)
  {
    if (champions->prog_number > max)
      max = champions->prog_number;
    champions = champions->next;
  }
  return (max);
}

int			load_champions_in_arena(unsigned char *arena,
						unsigned char *info_arena,
						t_corewar *core)
{
  t_champions		*tmp;

  if ((load_file_in_arena(arena, info_arena, core->champions)) == -1)
    return (-1);
  init_values_champions(core->champions);
  core->prog_number_max = find_max_prog_number(core->champions);
  tmp = core->champions;
  while (tmp)
  {
    get_cycle_to_wait(core, tmp);
    tmp = tmp->next;
  }
  if (core->nb_champions > 4)
    return (my_putstr("error: too many programmes (max = 4)\n", 2));
  return (0);
}
