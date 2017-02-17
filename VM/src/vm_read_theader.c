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

static unsigned int		get_magic(char *str)
{
	unsigned int ret;

	ft_memcpy(&ret, str, LENGTH_MAGIC);
	ft_endian_convert(&ret, 4);
	return (ret);
}

static int				get_name(char prog_name[], char *str)
{
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

int						vm_read_header(header_t *theader,
										char *str, int size_str)
{
	theader->magic = get_magic(str);
	if (theader->magic != COREWAR_EXEC_MAGIC)
	{
		msg_error_store("Magic number is wrong");
		return (-1);
	}
	get_name(theader->prog_name, str);
	theader->prog_size = get_prog_size(str);
	if (theader->prog_size > CHAMP_MAX_SIZE)
	{
		msg_error_store("The champion size is too big");
		return (-1);
	}
	get_comment(theader->comment, str);
	if (size_str - (LENGTH_BEFORE_INST) != (int)(theader->prog_size))
	{
		msg_error_store("Size is wrong");
		return (-1);
	}
	return (0);
}
