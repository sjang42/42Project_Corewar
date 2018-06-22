/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 18:03:05 by sjang             #+#    #+#             */
/*   Updated: 2017/02/04 18:03:06 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_MAP_H
# define VM_T_MAP_H

# include <vm_t_champion.h>
# include <vm_structures.h>
# include <libft.h>

int                 t_map_put_all(t_map *tmap, int fd[], int size);
t_map               *t_map_new(int size);
int                 t_map_put_chams(t_map *tmap, t_champion *tcham[], int num_cham);
int                 t_map_put_bytes(t_map *tmap, int where, void *bytes, int size);
void    t_map_destroy(t_map *tmap);

void    w_sti_reg_to_map(t_arena *tarena, int idx_cham, int where, void *bytes);

char    *ft_itoa_base(int value, int base);
void            t_map_dump(t_map *tmap);

#endif
