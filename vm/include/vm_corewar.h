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
# include <op.h>

typedef struct		s_map
{
	char	*map;
	int		size_map;
	int		num_cham;
}					t_map;

void				print_memory(const void *addr, size_t size);
int 				t_map_put_all(t_map *tmap, int fd[], int size);
t_map				*t_map_new(int size);
int					t_map_put_chams(t_map *tmap, t_champion *tcham[], int num_cham);


int					ft_endian_convert(void *src, size_t size);

void				*get_data(t_map *tmap, int pc, size_t size);
int					*get_bytecode(t_map *tmap, int pc_command, int num_arg);
int					put_registry(char **registry, int idx, long long src);
char 				get_current_byte(t_map *tmap, int pc);
char				get_indirect_data(t_map *tmap, int pc_command, int idx);
int					check_arg_byte(int opcode, int *arg_byte);

int					deal_command(int opcode, t_map *tmap, t_champion *tcham);



#endif