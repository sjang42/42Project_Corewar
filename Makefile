# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 04:36:22 by sjang             #+#    #+#              #
#    Updated: 2017/02/17 04:36:23 by sjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT					=	./libft/
FTPRINTF				=	./ftprintf
ASM						=	./ASM
VM						=	./VM

CLEAN					=	make clean -C
FCLEAN					=	make fclean -C

ifdef ALLOCWRAP
	LDFLAGS += $(HOME)/lib/alloc_wrap.c -ldl
endif 

.PHONY						:	clean fclean re

all							:
								make -C $(LIBFT)
								make -C $(FTPRINTF)
								make -C $(ASM)
								make -C $(VM)


# $(LIBFT)libft.a				:
# 								make -C $(LIBFT)

# $(FTPRINTF)libftprintf.a	:
# 								make -C $(FTPRINTF)

# asm							:
# 								make -C $(ASM)

# corewar						:
# 								make -C $(VM)


clean					:
							$(CLEAN) $(LIBFT)
							$(CLEAN) $(FTPRINTF)
							$(CLEAN) $(ASM)
							$(CLEAN) $(VM)

fclean					:	clean
							$(FCLEAN) $(LIBFT)
							$(FCLEAN) $(FTPRINTF)
							$(FCLEAN) $(ASM)
							$(FCLEAN) $(VM)

test					:	all
							make -C $(TEST) 

re						:	fclean all
