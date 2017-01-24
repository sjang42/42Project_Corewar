/*
** get_next_line.h for Corewar in /home/chapui_s/travaux/my_asm
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Apr 10 18:10:53 2014 chapui_s
** Last update Thu Apr 10 18:10:59 2014 chapui_s
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUF_SIZE	42

typedef struct	s_fd
{
  char		*str;
  int		fd;
  struct s_fd	*next;
}		t_fd;

char	*get_next_line(const int fd);

#endif
