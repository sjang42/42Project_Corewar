/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:14:44 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 18:14:46 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			get_prog_name(char prog_name[], t_strs *strs, char **error)
{
	char	*begin;
	char	*end;
	char	*tmp;

	if (strs->strarr[0] == ft_strstr(strs->strarr[0], NAME_CMD_STRING)
		&&
		ft_count_strch(strs->strarr[0], '"') == 2)
	{
		begin = ft_strchr(strs->strarr[0], '"') + 1;
		tmp = ft_strdup(begin);
		begin = ft_strchr(tmp, '"');
		*begin = 0;
		if (ft_strlen(tmp) > PROG_NAME_LENGTH)
		{
			free(tmp);
			*error = ft_strdup("Name is too long");
			return (-1);
		}
		ft_strcpy(prog_name, tmp);
		free(tmp);
	}
	else
	{
		*error = ft_strdup("Name should be at the first line");
		return (-1);
	}
	return (0);
}

int			get_comment(char comment[], t_strs *strs, char **error)
{
	char	*begin;
	char	*end;
	char	*tmp;

	if (strs->strarr[1] == ft_strstr(strs->strarr[1], COMMENT_CMD_STRING)
		&&
		ft_count_strch(strs->strarr[1], '"') == 2)
	{
		begin = ft_strchr(strs->strarr[1], '"') + 1;
		tmp = ft_strdup(begin);
		begin = ft_strchr(tmp, '"');
		*begin = 0;
		if (ft_strlen(tmp) > COMMENT_LENGTH)
		{
			free(tmp);
			*error = ft_strdup("Name is too long");
			return (-1);
		}
		ft_strcpy(comment, tmp);
		free(tmp);
	}
	else
	{
		*error = ft_strdup("Comment should be at the second line");
		return (-1);
	}
	return (0);
}

header_t	*get_header(t_strs *strs)
{
	header_t	*header;
	char		*error;

	header = (header_t*)malloc(sizeof(header_t));
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	header->magic = COREWAR_EXEC_MAGIC;
	ft_endian_ltob(&(header->magic), 4);
	if (get_prog_name(header->prog_name, strs, &error))
	{
		strs_destroy(strs);
		free(header);
		ft_exit_error_free(error);
	}
	if (get_comment(header->comment, strs, &error))
	{
		strs_destroy(strs);
		free(header);
		ft_exit_error_free(error);
	}
	return (header);
}
