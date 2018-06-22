/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:15:20 by sjang             #+#    #+#             */
/*   Updated: 2017/02/17 05:15:21 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_error.h>

char    *g_msg_error = NULL;

char    *msg_error_get(void)
{
    if (g_msg_error == NULL)
        return (NULL);
    else
        return (ft_strdup(g_msg_error));
}

void    msg_error_store(char *str)
{
    if (g_msg_error)
        free(g_msg_error);
    g_msg_error = ft_strdup(str);
}

void    msg_error_exit(void)
{
    if (g_msg_error)
        ft_exit_error_free(g_msg_error);
    else
        ft_exit_error(NULL);
}
