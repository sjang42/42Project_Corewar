/*
** main.c for Corewar in /home/chapui_s/travaux/Corewar/VM
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 20 14:45:46 2014 chapui_s
** Last update Sat Apr 12 18:55:43 2014 chapui_s
*/

#include "machine.h"

void		print_args(int *tmp_type, t_instruction *instruction, int i)
{
  if ((*tmp_type & 0b11000000) >> 6 == 1)
    my_putstr("r", 1);
  else if ((*tmp_type & 0b11000000) >> 6 == 0b10)
    my_putchar(DIRECT_CHAR);
  my_putnbr(instruction->params[i]);
  *tmp_type = *tmp_type << 2;
  if (*tmp_type & 0b11000000)
    my_putchar(SEPARATOR_CHAR);
}

void		print_instruction(t_instruction *instruction)
{
  int		tmp_type;
  int		i;

  i = 0;
  tmp_type = (instruction->type >> 2) << 2;
  while (op_tab[i].code && op_tab[i].code != instruction->code)
    i += 1;
  if (op_tab[i].code != 0)
  {
    my_putstr(op_tab[i].mnemonique, 1);
    my_putchar('\t');
    i = 0;
    if (instruction->code == LIVE || instruction->code == ZJMP
	|| instruction->code == FORK || instruction->code == LFORK)
    {
      (instruction->code == LIVE) ? (my_putchar(DIRECT_CHAR)) : (0);
      my_putnbr(instruction->params[0]);
    }
    while (tmp_type & 0b11000000)
    {
      print_args(&tmp_type, instruction, i);
      i += 1;
    }
  }
}

int		my_desassembler(t_corewar *core,
				t_champions *champions)
{
  int		pc_base;
  t_instruction	instruction;

  pc_base = champions->pc;
  if (champions->name)
  {
    my_putstr(".name\t\t\"", 1);
    my_putstr(champions->name, 1);
    my_putstr("\"\n", 1);
  }
  if (champions->comment)
  {
    my_putstr(".comment\t\"", 1);
    my_putstr(champions->comment, 1);
    my_putstr("\"\n", 1);
  }
  while (champions->pc < (pc_base + champions->size))
  {
    get_instruction(core, champions, &instruction);
    print_instruction(&instruction);
    my_putchar('\n');
  }
  return (0);
}

int		desassemble_it(t_corewar *core)
{
  t_champions	*tmp;
  int		is_filename;

  tmp = core->champions;
  is_filename = 0;
  if (tmp->next)
    is_filename = 1;
  while (tmp)
  {
    if (is_filename == 1)
    {
      my_putstr("\t[", 1);
      my_putstr(tmp->filename, 1);
      my_putstr("]\n", 1);
    }
    if (my_desassembler(core, tmp) == -1)
      return (-1);
    tmp = tmp->next;
  }
  return (0);
}
