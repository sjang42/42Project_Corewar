/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_arg.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:25:15 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 16:25:16 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_ARG_H
# define VM_T_ARG_H

# include <op.h>
# include <libft.h>
# include <vm_structures.h>

# include <vm_t_map.h>

/*
**              sizeof(byte_arg) == num_arg;
*/

void            *read_arg(t_map *tmap, int pc_command,
                            int opcode, int *bytecode);
int             *get_bytecode(t_map *tmap, int pc_command, int opcode);

void            t_arg_destroy(t_arg *targ);
t_arg           *t_arg_new(t_map *tmap, int pc_command, int opcode);

int             check_bytecode(int opcode, int *arg_byte);

void            *read_data(t_map *tmap, int pc, size_t size);
unsigned char   read_current_byte(t_map *tmap, int pc);

int             *read_bytecode(t_map *tmap, int pc_command, int num_arg);

#endif
