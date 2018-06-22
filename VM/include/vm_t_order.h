/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_order.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:23:38 by sjang             #+#    #+#             */
/*   Updated: 2017/02/20 00:23:39 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_ORDER_H
# define VM_T_ORDER_H

# include <vm_structures.h>
# include <libft.h>

t_order *t_order_new(int size);
void    t_order_store(t_order *torder, int idx_cham, int idx_tproc);
int     t_order_delete(t_order *torder, int idx_cham, int idx_tproc);

#endif
