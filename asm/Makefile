# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/30 12:18:56 by sjang             #+#    #+#              #
#    Updated: 2017/01/30 12:18:57 by sjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET					=	a.out

OBJECTS					=	op.o\
							file_to_strs.o\
							asm_t_strs.o\
							asm_t_inst.o\
							asm_t_label.o\
							main.o\
							asm_get_header.o\
							add_libft.o\
							asm_switch.o\
							asm_switch_type.o\
							asm_get_inst.o\
							asm_get_label.o\
							asm_asm.o\
							asm_error.o\



SRC						=	./src/
OP						=	../op/
ICL						=	./include/
CC						=	gcc
CFLAG					=	
RM						=	/bin/rm -f

HEADERS					=	$(ICL)asm.h\
							$(ICL)asm_t_inst.h\
							$(ICL)asm_t_label.h\
							$(ICL)asm_t_strs.h\
							$(OP)op.h

LIBFT					=	-L../libft -lft

.PHONY					:	clean fclean re

all						:	$(TARGET)

$(TARGET)				:	$(OBJECTS) $(HEADERS) ../libft/libft.a
							$(CC) $(CFLAG) -o $@ $(OBJECTS) $(LIBFT)

%.o						:	$(SRC)%.c
							$(CC) -c $(CFLAG) $< -I../libft/include -I$(ICL) -I$(OP)

%.o						:	$(OP)%.c
							$(CC) -c $(CFLAG) $< -I$(OP)
							
op.o					:	$(OP)op.c $(HEADERS)
main.o					:	$(SRC)main.c $(HEADERS)
file_to_strs.o			:	$(SRC)file_to_strs.c $(HEADERS)
asm_t_strs.o			:	$(SRC)asm_t_strs.c $(HEADERS)
asm_t_inst.o			:	$(SRC)asm_t_inst.c $(HEADERS)
asm_t_label.o			:	$(SRC)asm_t_label.c $(HEADERS)
asm_get_header.o		:	$(SRC)asm_get_header.c $(HEADERS)
add_libft.o				:	$(SRC)add_libft.c $(HEADERS)
asm_switch.o			:	$(SRC)asm_switch.c $(HEADERS)
asm_switch_type.o		:	$(SRC)asm_switch_type.c $(HEADERS)
asm_get_inst.o	m		:	$(SRC)asm_get_inst.c $(HEADERS)
asm_get_label.o	m		:	$(SRC)asm_get_label.c $(HEADERS)
asm_asm.o	m			:	$(SRC)asm_asm.c $(HEADERS)
asm_error.o	m			:	$(SRC)asm_error.c $(HEADERS)

clean					:
							$(RM) $(OBJECTS)
fclean					:	clean
							$(RM) $(TARGET)
re						:	fclean all

