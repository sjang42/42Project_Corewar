# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 16:39:33 by sjang             #+#    #+#              #
#    Updated: 2017/02/01 16:39:34 by sjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET					=	a.out

OBJECTS					=	main.o\
							vm_print_memory.o\
							vm_t_map.o\
							\
							vm_t_proc.o\
							vm_t_champion.o\
							vm_read_theader.o\
							\
							add_libft.o


SRC						=	./src/
ICL						=	./include/
SRC_ASM					=	../asm/src/
ICL_ASM					=	../asm/include/
ICL_LIBFT				=	../libft/include/

CC						=	gcc
CFLAG					=	
RM						=	/bin/rm -f

HEADERS					=	$(ICL)vm_corewar.h\
							$(ICL)vm_t_champion.h\
							$(ICL)vm_t_proc.h\
							$(ICL_ASM)asm_t_inst.h\
							$(OP)op.h

LIBFT					=	-L../libft -lft

OP						=	../op/

.PHONY					:	clean fclean re

all						:	$(TARGET)

$(TARGET)				:	$(OBJECTS) $(HEADERS) ../libft/libft.a
							$(CC) $(CFLAG) -o $@ $(OBJECTS) $(LIBFT)

%.o						:	$(SRC)%.c
							$(CC) -c $(CFLAG) $< -I$(ICL_LIBFT) -I$(ICL) -I$(ICL_ASM) -I$(OP) 

%.o						:	$(OP)%.c
							$(CC) -c $(CFLAG) $< -I$(OP)

main.o					:	$(SRC)main.c $(HEADERS)
vm_print_memory.o		:	$(SRC)vm_print_memory.c $(HEADERS)
vm_t_map.o				:	$(SRC)vm_t_map.c $(HEADERS)
vm_t_proc.o				:	$(SRC)vm_t_proc.c $(HEADERS)
vm_t_champion.o			:	$(SRC)vm_t_champion.c $(HEADERS)
vm_read_theader.o		:	$(SRC)vm_read_theader.c $(HEADERS)

add_libft.o				:	$(SRC)add_libft.c $(HEADERS)

clean					:
							$(RM) $(OBJECTS)
fclean					:	clean
							$(RM) $(TARGET)
re						:	fclean all
