/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 01:43:07 by sjang             #+#    #+#             */
/*   Updated: 2017/02/08 01:43:09 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_option.h>
#include <libft.h>

static int			ft_decide_option(char *str)
{
	if (MAX_OP > 0 && !ft_strcmp(str, OPTION1_STR))
		return (OPTION1);
	if (MAX_OP > 1 && !ft_strcmp(str, OPTION2_STR))
		return (OPTION2);
	if (MAX_OP > 2 && !ft_strcmp(str, OPTION3_STR))
		return (OPTION3);
	if (MAX_OP > 3 && !ft_strcmp(str, OPTION4_STR))
		return (OPTION4);
	if (MAX_OP > 4 && !ft_strcmp(str, OPTION5_STR))
		return (OPTION5);
	return (OPTION_NOTHING);
}

int						jump_arg(int tmp)
{
	int ret;

	ret = 1;
	if (tmp == OPTION1)
		return (OPTION1_ARG + 1);
	else if (tmp == OPTION2)
		return (OPTION2_ARG + 1);
	else if (tmp == OPTION3)
		return (OPTION3_ARG + 1);
	else if (tmp == OPTION4)
		return (OPTION4_ARG + 1);
	else if (tmp == OPTION5)
		return (OPTION5_ARG + 1);
	else
		return (1);
}
int						ft_get_option(
						int argc, char *argv[],
						int *option)
{
	int			tmp;
	int			i;

	*option = OPTION_NOTHING;
	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		tmp = ft_decide_option(argv[i]);
		if (tmp == OPTION_NOTHING)
			return (i);
		*option |= tmp;
		i += jump_arg(tmp);
	}
	return (i);
}
