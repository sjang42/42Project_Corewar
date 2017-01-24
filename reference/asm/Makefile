##
## Makefile for Corewar in /home/chapui_s/travaux/my_asm
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Thu Apr 10 18:23:50 2014 chapui_s
## Last update Sat Apr 12 15:52:49 2014 poulet_a
##

NAME	= asm

SRC	= main.c \
	  get_next_line.c \
	  my_putstr.c \
	  list_file.c \
	  my_strlen.c \
	  my_str_to_wordtab.c \
	  is_type.c \
	  my_strcmp.c \
	  get_size.c \
	  int_to_str.c \
	  resolve_label.c \
	  remove_bad_stuff.c \
	  my_atoi.c \
	  my_showmem.c \
	  find_type.c \
	  write_bytes.c \
	  write_bytes_tools.c \
	  is_special_case.c \
	  get_name_comment.c \
	  convert_endian.c \
	  get_header.c \
	  free_asm.c \
	  my_strchr.c \
	  check_instruction.c \
	  msg_bad.c \
	  write_file.c \
	  read_file.c \
	  ../op/op.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
