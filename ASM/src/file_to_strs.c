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

static void         ft_remove_tabs(char **str)
{
    int     i;
    char    *tmp;
    char    *tmp2;

    i = 0;
    tmp = ft_strdel_repeat(*str, ' ');
    tmp2 = ft_strdel_repeat(tmp, '\t');
    free(tmp);
    while ((tmp2)[i])
    {
        if ((tmp2)[i] == '\t')
            (tmp2)[i] = ' ';
        i++;
    }
    tmp = ft_strdel_repeat(tmp2, ' ');
    free(tmp2);
    free(*str);
    *str = tmp;
}

static int          ft_devide_label(char *str, t_strs *strs)
{
    char    *label;
    int     i;

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

static char         *fts_trim_line(char *line)
{
    char    *adr_comment;
    char    *trimed;

    adr_comment = ft_strchr(line, ';');
    if (adr_comment)
        *adr_comment = 0;
    adr_comment = ft_strchr(line, COMMENT_CHAR);
    if (adr_comment)
        *adr_comment = 0;
    trimed = ft_strtrim(line);
    ft_remove_tabs(&trimed);
    free(line);
    return (trimed);
}

t_strs              *file_to_strs(int fd)
{
    t_strs  *strs;
    char    *line;
    char    *trimed;
    int     label_char;

    strs = strs_new(100);
    while (get_next_line(fd, &line))
    {
        if (!line || line[0] == COMMENT_CHAR || line[0] == 0)
        {
            free(line);
            continue ;
        }
        trimed = fts_trim_line(line);
        if (trimed[0] == '\0')
        {
            free(trimed);
            continue ;
        }
        label_char = ft_devide_label(trimed, strs);
        (label_char) ?
            strs_addone(strs, trimed + label_char + 1) :
            strs_addone(strs, trimed);
    }
    return (strs);
}
