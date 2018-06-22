/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:31:00 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 15:31:02 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void    show_usage(char *filename)
{
    ft_putstr("Usage : ");
    ft_putstr(filename);
    ft_putstr(" <sourcefile.s>\n");
}

void    show_usage_exit(char *filename)
{
    show_usage(filename);
    exit(-1);
}

int     check_argv(int argc, char *argv[])
{
    char    *tmp;

    if (argc != 2)
    {
        return (-1);
    }
    tmp = ft_strstr(argv[1], ".s");
    if (!tmp ||
        *(tmp + 2) != 0)
    {
        return (-1);
    }
    return (0);
}
