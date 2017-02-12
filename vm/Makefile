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

OBJECTS					=	op.o\
							\
							main.o\
							\
							vm_t_map.o\
							vm_t_map_dump.o\
							\
							vm_t_proc.o\
							\
							vm_t_champion.o\
							vm_t_champion_part2.o\
							vm_t_champion_part3.o\
							vm_read_theader.o\
							\
							vm_deal_command.o\
							vm_deal_command_sub1.o\
							vm_deal_command_sub2.o\
							\
							vm_execute.o\
							\
							vm_t_arg.o\
							vm_t_arg_sub.o\
							\
							vm_t_arena.o\
							vm_t_arena_checkup.o\
							\
							\
							vm_execute_live.o\
							vm_execute_ld.o\
							vm_execute_st.o\
							vm_execute_add.o\
							vm_execute_sub.o\
							vm_execute_sti.o\
							vm_execute_and.o\
							vm_execute_or.o\
							vm_execute_xor.o\
							vm_execute_zjmp.o\
							vm_execute_ldi.o\
							vm_execute_lld.o\
							vm_execute_lldi.o\
							vm_execute_aff.o\
							vm_execute_fork.o\
							vm_execute_lfork.o\
							\
							vm_ncurses.o\
							vm_ncurses_show_map.o\
							vm_ncurses_colors.o\
							\
							vm_ncurses_info.o\
							\
							ft_option.o\
							\
							vm_show_commands.o\
							\
							add_libft.o\
							ft_itoa_base.o


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
NCURSES					=	-lncurses

OP						=	../op/

.PHONY					:	clean fclean re

all						:	$(TARGET)

$(TARGET)				:	$(OBJECTS) $(HEADERS) ../libft/libft.a
							$(CC) $(CFLAG) -o $@ $(OBJECTS) $(LIBFT) $(NCURSES)

%.o						:	$(SRC)%.c
							$(CC) -c $(CFLAG) $< -I$(ICL_LIBFT) -I$(ICL) -I$(ICL_ASM) -I$(OP) 

%.o						:	$(OP)%.c
							$(CC) -c $(CFLAG) $< -I$(OP)

op.o					:	$(OP)op.c $(HEADERS)

main.o					:	$(SRC)main.c $(HEADERS)

vm_t_map.o				:	$(SRC)vm_t_map.c $(HEADERS)
vm_t_map_dump.o			:	$(SRC)vm_t_map_dump.c $(HEADERS)

vm_t_proc.o				:	$(SRC)vm_t_proc.c $(HEADERS)
vm_t_champion.o			:	$(SRC)vm_t_champion.c $(HEADERS)
vm_t_champion_part2.o	:	$(SRC)vm_t_champion_part2.c $(HEADERS)
vm_t_champion_part3.o	:	$(SRC)vm_t_champion_part3.c $(HEADERS)
vm_read_theader.o		:	$(SRC)vm_read_theader.c $(HEADERS)

vm_deal_command.o		:	$(SRC)vm_deal_command.c $(HEADERS)
vm_deal_command_sub1.o	:	$(SRC)vm_deal_command_sub1.c $(HEADERS)
vm_deal_command_sub2.o	:	$(SRC)vm_deal_command_sub2.c $(HEADERS)

vm_execute.o			:	$(SRC)vm_execute.c $(HEADERS)

vm_t_arg.o				:	$(SRC)vm_t_arg.c $(HEADERS)
vm_t_arg_sub.o			:	$(SRC)vm_t_arg_sub.c $(HEADERS)

vm_t_arena.o			:	$(SRC)vm_t_arena.c $(HEADERS)
vm_t_arena_checkup.o	:	$(SRC)vm_t_arena_checkup.c $(HEADERS)

add_libft.o				:	$(SRC)add_libft.c $(HEADERS)

vm_execute_live.o		:	$(SRC)vm_execute_live.c $(HEADERS)
vm_execute_ld.o			:	$(SRC)vm_execute_ld.c $(HEADERS)
vm_execute_st.o			:	$(SRC)vm_execute_st.c $(HEADERS)
vm_execute_add.o		:	$(SRC)vm_execute_add.c $(HEADERS)
vm_execute_sub.o		:	$(SRC)vm_execute_sub.c $(HEADERS)
vm_execute_sti.o		:	$(SRC)vm_execute_sti.c $(HEADERS)
vm_execute_and.o		:	$(SRC)vm_execute_and.c $(HEADERS)
vm_execute_or.o			:	$(SRC)vm_execute_or.c $(HEADERS)
vm_execute_xor.o		:	$(SRC)vm_execute_xor.c $(HEADERS)
vm_execute_zjmp.o		:	$(SRC)vm_execute_zjmp.c $(HEADERS)
vm_execute_ldi.o		:	$(SRC)vm_execute_ldi.c $(HEADERS)
vm_execute_lld.o		:	$(SRC)vm_execute_lld.c $(HEADERS)
vm_execute_lldi.o		:	$(SRC)vm_execute_lldi.c $(HEADERS)
vm_execute_aff.o		:	$(SRC)vm_execute_aff.c $(HEADERS)
vm_execute_fork.o		:	$(SRC)vm_execute_fork.c $(HEADERS)
vm_execute_lfork.o		:	$(SRC)vm_execute_lfork.c $(HEADERS)

vm_show_commands.o		:	$(SRC)vm_show_commands.c $(HEADERS)


vm_ncurses.o			:	$(SRC)vm_ncurses.c $(HEADERS)
vm_ncurses_show_map.o	:	$(SRC)vm_ncurses_show_map.c $(HEADERS)
vm_ncurses_colors.o		:	$(SRC)vm_ncurses_colors.c $(HEADERS)

vm_ncurses_info.o		:	$(SRC)vm_ncurses_info.c $(HEADERS)



ft_option.o				:	$(SRC)ft_option.c $(HEADERS)
ft_itoa_base.o			:	$(SRC)ft_itoa_base.c $(HEADERS)

clean					:
							$(RM) $(OBJECTS)
fclean					:	clean
							$(RM) $(TARGET)
re						:	fclean all
