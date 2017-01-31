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

#include "asm.h"

int			get_grog_name(char prog_name[], t_strs *strs)
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
			printf("%s\n", "error : too long name");
		ft_strcpy(prog_name, tmp);
		free(tmp);
	}
	else
		printf("%s\n", "error : no name");
	return (0);
}

int			get_comment(char comment[], t_strs *strs)
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
			printf("%s\n", "error : too long cooment");
		ft_strcpy(comment, tmp);
		free(tmp);
	}
	else
		printf("%s\n", "error : no comment");
	return (0);
}

header_t	*get_header(t_strs *strs)
{
	header_t	*header;

	header = (header_t*)malloc(sizeof(header_t));
	header->magic = COREWAR_EXEC_MAGIC;
	get_grog_name(header->prog_name, strs);
	get_comment(header->comment, strs);
	return (header);
}
