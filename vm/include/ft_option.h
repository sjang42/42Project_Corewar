/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 01:43:37 by sjang             #+#    #+#             */
/*   Updated: 2017/02/08 01:43:38 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPTION_H
# define FT_OPTION_H

# define OPTION0 NOTHING
# define OPTION1 DUMP
# define OPTION2 NCURSES
# define OPTION3 COMMANDS
# define OPTION4 CYCLE
# define OPTION5 ADD5

# define OPTION1_STR "-dump"
# define OPTION2_STR "-v"
# define OPTION3_STR "-c"
# define OPTION4_STR "-cycle"
# define OPTION5_STR "add"

# define OPTION1_ARG 1
# define OPTION2_ARG 0
# define OPTION3_ARG 0
# define OPTION4_ARG 0
# define OPTION5_ARG 0

# define MAX_OP 4

enum
{
	OPTION_NOTHING = 0,
	OPTION1 = 1,
	OPTION2 = 2,
	OPTION3 = 4,
	OPTION4 = 8,
	OPTION5 = 16,
};

int					ft_get_option(
					int argc, char *argv[],
					int *option);

#endif
