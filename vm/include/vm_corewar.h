/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:15:18 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 16:15:20 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_COREWAR_H
# define VM_COREWAR_H

# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <vm_t_champion.h>
# include <vm_t_proc.h>
# include <vm_t_arg.h>
# include <vm_t_map.h>
# include <op.h>

typedef int		TYPE_DIR;
typedef int		TYPE_REG;
typedef short	TYPE_IND;

enum
{
	OP_LIVE = 0,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF,
};

# define MIN_OPCODE 1
# define MAX_OPCODE 16

void				print_memory(const void *addr, size_t size);
int 				t_map_put_all(t_map *tmap, int fd[], int size);
t_map				*t_map_new(int size);
int					t_map_put_chams(t_map *tmap, t_champion *tcham[], int num_cham);
int					t_map_put_bytes(t_map *tmap, int where, void *bytes, int size);

int					ft_endian_convert(void *src, size_t size);

void				*read_data(t_map *tmap, int pc, size_t size);
int					*read_bytecode(t_map *tmap, int pc_command, int num_arg);
int		put_registry(char **registry, int idx, void *src);
char 				read_current_byte(t_map *tmap, int pc);
char				read_indirect_data(t_map *tmap, int pc_command, int idx);
int					check_bytecode(int opcode, int *arg_byte);

int deal_command(t_map *tmap, t_proc *tproc, int opcode, int pc_command);

int					get_registry(char **registry, int idx, void *dest);


int					is_opcode(char byte);
int					get_cycle(int opcode);
int					vm_execute_proc(t_map *tmap, t_proc *tproc);

int				read_registry(char **registry, int idx, void *dest);

#endif