/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 17:42:01 by sjang             #+#    #+#             */
/*   Updated: 2017/01/28 17:42:02 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		main(int argc, char *argv[])
{
	int			fd;
	int			fd2;
	int			zero;

	if (check_argv(argc, argv))
		show_usage_exit(argv[0]);
	ft_asm(argv[1]);
	return (0);
}
