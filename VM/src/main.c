/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:14:26 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 16:14:27 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_corewar.h>

void	vm_show_usage(char *filename)
{
	ft_putstr("***************************************************\
*****************\n");
	ft_putstr("Usage: ");
	ft_putstr(filename);
	ft_putstr(" [-dump N | -cycle | -commands | -live] [-v]\n");
	ft_putstr("        [-n N] <champion1.cor> <...>\n");
	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -dump N   : dump the memory after\
executing cycles as many as N\n");
	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -cycle    : Shows the flow of cycle, period\n");
	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -commands : Shows the commands executed\n");
	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -live     : Shows executed live. default is off\n");
	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -v        : Shows corewar in ncurses arena\n");
	ft_putstr("              It can't be used with other options except -n\n");

	ft_putstr("\n***************************************************\
*****************\n");
	ft_putstr("  -n N      : It specifies the number of champion.\n");
	ft_putstr("              It affects the order of champions in the corewar.\n");
	ft_putstr("              N is interpreted as an int value.\n");
	ft_putstr("\n***************************************************\
*****************\n");
}

int		main(int argc, char *argv[])
{
	if (argc < 2)
	{
		vm_show_usage(argv[1]);
		return (0);
	}
	corewar(argc, argv);
	return (0);
}
