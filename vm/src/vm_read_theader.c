/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_theader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:01:55 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 15:01:59 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_header.h>
#include <stdio.h>//

int		ft_endian_convert(void *src, size_t size);

static unsigned int		get_magic(char *str)
{
	unsigned int ret;

	ft_memcpy(&ret, str, LENGTH_MAGIC);
	ft_endian_convert(&ret, 4);
	return (ret);
}		

static int				get_name(char prog_name[], char *str)
{
	int 	i;

	ft_memcpy(prog_name, str + LENGTH_MAGIC, PROG_NAME_LENGTH);
	prog_name[PROG_NAME_LENGTH] = '\0';
	return (0);
}

static unsigned int		get_prog_size(char *str)
{
	unsigned int ret;

	ft_memcpy(
		&ret,
		str + LENGTH_MAGIC + PROG_NAME_LENGTH + 4,
		LENGTH_PROG_SIZE);
	ft_endian_convert(&ret, 4);
	return (ret);
}

static int				get_comment(char comment[], char *str)
{
	ft_memcpy(
		comment,
		str + LENGTH_MAGIC + PROG_NAME_LENGTH + 4 + LENGTH_PROG_SIZE,
		COMMENT_LENGTH);
	comment[COMMENT_LENGTH] = '\0';
	return (0);
}

int						vm_read_header(header_t *theader, int fd,
										char *str, int size_str)
{
	theader->magic = get_magic(str);
	get_name(theader->prog_name, str);
	theader->prog_size = get_prog_size(str);
	get_comment(theader->comment, str);

	if (size_str - (LENGTH_BEFORE_INST) != theader->prog_size)
	{
		printf("%d\n", size_str);
		printf("%d\n", LENGTH_BEFORE_INST);
		printf("%d\n", size_str - (LENGTH_BEFORE_INST));
		printf("%d\n", theader->prog_size);
		ft_exit_error("Size is wrong");
	}
	return (0);
}
