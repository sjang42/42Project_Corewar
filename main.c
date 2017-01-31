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

#include "asm.h"

char	get_instruction(t_strs *strs)
{
	int i;

	i = 0;
	while (i < strs->size_strarr)
	{
		printf("opcode : %d\n", switch_instruction(strs->strarr[i]));
		i++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	int			fd;
	int			magic = 0xea83f3;
	t_strs		*strs;
	header_t	*header;
	int 		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	strs = file_to_strs(fd);
	header = get_header(strs);
	while (i < strs->size_strarr)
	{
		printf("%s\n", strs->strarr[i]);
		// printf("opcode : %d\n", switch_instruction(strs->strarr[i]));
		i++;
	}
	// printf("name : %s\n", header->prog_name);
	// printf("comment : %s\n", header->comment);
	
	return (0);
}
