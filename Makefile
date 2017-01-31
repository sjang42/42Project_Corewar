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

OBJECTS					=	file_to_strs.o\
							t_strs.o\
							main.o\
							asm_get_header.o\
							add_libft.o\
							asm_switch.o\

SRC						=	./
ICL						=	./
CC						=	gcc
CFLAG					=	
RM						=	/bin/rm -f

HEADERS					=	$(ICL)asm.h
LIBFT					=	-L./libft -lft

.PHONY					:	clean fclean re

all						:	$(TARGET)

$(TARGET)				:	$(OBJECTS) $(HEADERS) ./libft/libft.a
							$(CC) $(CFLAG) -o $@ $(OBJECTS) $(LIBFT)

%.o						:	$(SRC)%.c
							$(CC) -c $(CFLAG) $< -I./libft/include

main.o					:	$(SRC)main.c $(HEADERS)
file_to_strs.o			:	$(SRC)file_to_strs.c $(HEADERS)
t_strs.o				:	$(SRC)t_strs.c $(HEADERS)
asm_get_header.o		:	$(SRC)asm_get_header.c $(HEADERS)
add_libft.o				:	$(SRC)add_libft.c $(HEADERS)
asm_switch.o			:	$(SRC)asm_switch.c $(HEADERS)

clean					:
							$(RM) $(OBJECTS)
fclean					:	clean
							$(RM) $(TARGET)
re						:	fclean all

