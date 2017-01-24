##
## Makefile for  in /home/poulet_a/projets/corewar
## 
## Made by poulet_a
## Login   <poulet_a@epitech.net>
## 
## Started on  Tue Mar 11 08:22:15 2014 poulet_a
## Last update Thu Mar 13 17:06:18 2014 poulet_a
##

CC	=	cc

RM	=	rm -f

CFLAGS	+=	-W -Wall -pedantic

LFLAGS	+=	-Iop

NAME	=	corewar

all:		$(NAME)

$(NAME):
		make -Casm
		make -Ccorewar

clean:
		make clean -Casm
		make clean -Ccorewar

fclean:
		make fclean -Casm
		make fclean -Ccorewar

re:		fclean all

.PHONY:		clean fclean all re $(NAME)
