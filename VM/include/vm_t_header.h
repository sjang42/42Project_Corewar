/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:55:43 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 15:55:45 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_T_HEADER_H
# define VM_T_HEADER_H

# include <op.h>
# include <libft.h>
# include <vm_structures.h>
# include <vm_error.h>

int		vm_read_header(header_t *theader, char *str, int size_str);

#endif
