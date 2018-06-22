/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:18:38 by sjang             #+#    #+#             */
/*   Updated: 2017/02/17 05:18:39 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_ERROR_H
# define VM_ERROR_H

# include <libft.h>

char    *msg_error_get(void);
void    msg_error_store(char *str);
void    msg_error_exit(void);

#endif
