/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:01:44 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 12:01:45 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void			ft_remove_tabs(char **str)
{
	int i;

	i = 0;
	ft_remove_overlap(str, ' ');
	ft_remove_overlap(str, '	');
	while ((*str)[i])
	{
		if ((*str)[i] == '\t')
			(*str)[i] = ' ';
		i++;
	}
	ft_remove_overlap(str, ' ');
}

static int			ft_devide_label(char *str, t_strs *strs)
{
	char *label;
	int		i;

	i = 0;
	if (ft_strchr(str, LABEL_CHAR) &&
		ft_strchr(str, ' ') > ft_strchr(str, LABEL_CHAR))
	{
		label = ft_strdup(str);
		while (label[i] != ' ')
			i++;
		label[i] = 0;
		strs_addone(strs, label);
		free(label);		
	}
	return (i);
}

t_strs				*file_to_strs(int fd)
{
	t_strs	*strs;
	char	*line;
	char	*adr_comment;
	char	*trimed;
	int		label_char;

	strs = strs_new(100);
	while (get_next_line(fd, &line))
	{
		if (line[0] != COMMENT_CHAR && line[0] != 0)
		{
			adr_comment = ft_strchr(line, ';');
			if (adr_comment)
				*adr_comment = 0;
			adr_comment = ft_strchr(line, COMMENT_CHAR);
			if (adr_comment)
				*adr_comment = 0;
			trimed = ft_strtrim(line);
			ft_remove_tabs(&trimed);
			//debug
				if (trimed[0] == '\0')
				{
					free(line);
					free(trimed);
					continue ;
				}
				// printf("trim : %s\n", trimed);
			//debug
			label_char = ft_devide_label(trimed, strs);
			free(line);
			line = trimed;
			if (label_char)
				strs_addone(strs, line + label_char + 1);
			else
				strs_addone(strs, line);
		}
		free(line);
	}
	return (strs);
}
