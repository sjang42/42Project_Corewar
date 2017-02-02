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



SRC						=	./src/
ICL						=	./include/
CC						=	gcc
CFLAG					=	
RM						=	/bin/rm -f

HEADERS					=	$(ICL)vm_corewar.h $(OP)op.h
LIBFT					=	-L../libft -lft

OP						=	../op/

.PHONY					:	clean fclean re

all						:	$(TARGET)

$(TARGET)				:	$(OBJECTS) $(HEADERS) ../libft/libft.a
							$(CC) $(CFLAG) -o $@ $(OBJECTS) $(LIBFT)

%.o						:	$(SRC)%.c
							$(CC) -c $(CFLAG) $< -I../libft/include -I$(ICL) -I$(OP)

%.o						:	$(OP)%.c
							$(CC) -c $(CFLAG) $< -I$(OP)

main.o					:	$(SRC)main.c $(HEADERS)
vm_print_memory.o		:	$(SRC)vm_print_memory.c $(HEADERS)
vm_t_map.o				:	$(SRC)vm_t_map.c $(HEADERS)

clean					:
							$(RM) $(OBJECTS)
fclean					:	clean
							$(RM) $(TARGET)
re						:	fclean all


