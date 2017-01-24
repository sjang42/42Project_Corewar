##
## Makefile for Corewar in /home/chapui_s/travaux/Corewar/VM
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Thu Mar 20 16:53:03 2014 chapui_s
## Last update Sat Apr 12 18:36:42 2014 chapui_s
##

NAME		= corewar

UTIL_DIR	= utils

GUI_DIR		= gui

FUNC_DIR	= functions

EXEC_DIR	= exec_instructions

SRC		= main.c \
		  desassembleur.c \
		  arguments.c \
		  list_champions.c \
		  load_arena.c \
		  load_champions_in_arena.c \
		  $(UTIL_DIR)/init_arena.c \
	  	  $(UTIL_DIR)/usage.c \
	  	  $(UTIL_DIR)/my_strcmp.c \
	  	  $(UTIL_DIR)/my_puts.c \
	  	  $(UTIL_DIR)/read_write_arena.c \
	  	  $(UTIL_DIR)/get_magic.c \
	  	  $(UTIL_DIR)/int_to_str.c \
	  	  $(UTIL_DIR)/my_atoi.c \
	  	  $(UTIL_DIR)/convert_endian.c \
	  	  $(UTIL_DIR)/my_showmem.c \
	  	  $(UTIL_DIR)/attribute_prog_number.c \
	  	  $(UTIL_DIR)/attribute_address.c \
	  	  $(UTIL_DIR)/my_strlen.c \
		  $(UTIL_DIR)/my_strcat.c \
		  $(UTIL_DIR)/my_strdup.c \
	  	  $(UTIL_DIR)/swap_int.c \
	  	  $(UTIL_DIR)/check_place_arena.c \
	  	  $(UTIL_DIR)/get_size.c \
	  	  $(UTIL_DIR)/sort_int.c \
	  	  $(UTIL_DIR)/check_args.c \
	  	  $(UTIL_DIR)/attribute_one_two_three_addr.c \
	  	  $(UTIL_DIR)/get_info_champions.c \
		  $(GUI_DIR)/my_gui.c \
		  $(GUI_DIR)/get_img.c \
		  $(GUI_DIR)/events.c \
		  $(GUI_DIR)/hex_to_str.c \
		  $(GUI_DIR)/get_color.c \
		  $(GUI_DIR)/load_players_name.c \
		  $(GUI_DIR)/disp_info_players.c \
		  $(EXEC_DIR)/exec_instructions.c \
		  $(EXEC_DIR)/get_instruction.c \
		  $(EXEC_DIR)/check_live.c \
		  $(FUNC_DIR)/my_live.c \
		  $(FUNC_DIR)/is_type.c \
		  $(FUNC_DIR)/my_ld.c \
		  $(FUNC_DIR)/my_lld.c \
		  $(FUNC_DIR)/my_st.c \
		  $(FUNC_DIR)/my_add.c \
		  $(FUNC_DIR)/my_sub.c \
		  $(FUNC_DIR)/my_and.c \
		  $(FUNC_DIR)/my_or.c \
		  $(FUNC_DIR)/my_xor.c \
		  $(FUNC_DIR)/my_ldi.c \
		  $(FUNC_DIR)/my_lldi.c \
		  $(FUNC_DIR)/my_sti.c \
		  $(FUNC_DIR)/my_zjmp.c \
		  $(FUNC_DIR)/my_fork.c \
		  $(FUNC_DIR)/my_lfork.c \
		  $(FUNC_DIR)/my_aff.c \
		  $(FUNC_DIR)/is_good_register.c \
		  ../op/op.c

OBJ		= $(SRC:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		+=-Wall -Wextra
CFLAGS		+= -L./SDL -lSDL -lSDL_ttf -Xlinker "-rpath=./SDL"

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
