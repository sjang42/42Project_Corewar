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
# include <vm_t_order.h>
# include <op.h>
# include <vm_t_arena.h>
# include <vm_ncurses.h>
# include <vm_structures.h>
# include <ft_printf.h>
# include <ft_option.h>
# include <vm_error.h>

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

# define DIR_ADR_SIZE               (IND_SIZE)

# define MIN_OPCODE                 1
# define MAX_OPCODE                 16



void                corewar(int argc, char *argv[]);

int                 ft_endian_convert(void *src, size_t size);

void                *read_data(t_map *tmap, int pc, size_t size);
int                 put_registry(char **registry, int idx, void *src);
unsigned char       read_current_byte(t_map *tmap, int pc);
char                read_indirect_data(t_map *tmap, int pc_command, int idx);
int                 check_bytecode(int opcode, int *arg_byte);

int                 deal_command(t_map *tmap, int idx_cham,
                                    int idx_proc, t_arena *tarena);

int                 get_registry(char **registry, int idx, void *dest);


// int                  is_opcode(char byte);
// int                  get_cycle(int opcode);

int             read_registry(char **registry, int idx, void *dest);

int             deal_live(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc);
int             deal_ld(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_st(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc);
int             deal_add(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_sub(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_sti(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc);
int             deal_and(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_or(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_xor(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_zjmp(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_ldi(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_lld(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_lldi(t_arena *tarena, t_map *tmap, int pc_command, t_proc *tproc);
int             deal_aff(t_arena *tarena, int idx_cham, int idx_proc);
int             deal_fork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command);
int             deal_lfork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command);


int             w_deal_live(t_arena *tarena, t_map *tmap, int idx_cham, int idx_proc);
int             w_deal_sti(t_arena *tarena, int idx_cham, int idx_proc);
int             w_deal_fork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command);
int             w_deal_lfork(t_arena *tarena, int idx_cham, int idx_proc, int pc_command);
int             w_deal_st(t_arena *tarena, int idx_cham, int idx_proc);


int             count_bytecode_cycle(t_map *tmap, int opcode, int pc_command);
char            *ft_itoa_base(int value, int base);


void        show_commands_ldi(t_arg *targ, t_type_arg type_arg, t_proc *tproc, int where);
void        show_commands_lldi(t_arg *targ, t_type_arg type_arg,
                                t_proc *tproc, int where);
void        show_commands_sti(t_arg *targ, t_type_arg type_arg,
                                t_proc *tproc, int where);
void        show_commands_zjmp(t_proc *tproc, int where);
void        show_commands_st(t_proc *tproc, t_arg *targ, int where);
void        show_commands_lld(t_proc *tproc, t_type_arg type_arg);
void        show_commands_ld(t_proc *tproc, t_type_arg type_arg);
void        show_commands_fork(t_proc *tproc, t_type_arg type_arg, int where);
void        show_commands_lfork(t_proc *tproc, t_type_arg type_arg, int where);
void        show_commands_live(t_proc *tproc, int num);
void        show_commands_sub(t_proc *tproc, t_arg *targ);
void        show_commands_add(t_proc *tproc, t_arg *targ);
void        show_commands_xor(t_proc *tproc, t_arg *targ, t_type_arg type_arg);
void        show_commands_and(t_proc *tproc, t_arg *targ, t_type_arg type_arg);
void        show_commands_or(t_proc *tproc, t_arg *targ, t_type_arg type_arg);

t_arg       *get_ret_targ(t_map *tmap, int *ret, int opcode, int pc_command);
int         read_rgies(t_proc *tproc, t_arg *targ, t_type_arg *type_arg);










#endif