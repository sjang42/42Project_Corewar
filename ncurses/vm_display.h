/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_display.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:35:52 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 18:35:53 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_DISPLAY_H
# define VM_DISPLAY_H

# include <op.h>

# define CONTENTS_BYTES_PER_LINE		64
# define CONTENTS_CHARS_PER_LINE		(CONTENTS_BYTES_PER_LINE * 3 - 1)
# define CONTENTS_LINES_FOR_MEM			(MEM_SIZE / CONTENTS_BYTES_PER_LINE)

# define CONTENTS_CHARS_PREFIX_HOR		2
# define CONTENTS_CHARS_SUFFIX_HOR		2

# define CONTENTS_CHARS_PREFIX_VER		1
# define CONTENTS_CHARS_SUFFIX_VER		1

# define INFO_CHARS						56

# define TOTAL_COLS						(CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_SUFFIX_HOR +\
										INFO_CHARS + 3)

# define TOTAL_LINES					(CONTENTS_CHARS_PREFIX_VER +\
										CONTENTS_LINES_FOR_MEM +\
										CONTENTS_CHARS_SUFFIX_VER + 2)


# define DIVIDE_VER_FIRST				(0)
# define DIVIDE_VER_SECOND				(1 + CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_SUFFIX_HOR)

# define DIVIDE_VER_THIRD				(1 + CONTENTS_CHARS_PREFIX_HOR +\
										CONTENTS_CHARS_PER_LINE +\
										CONTENTS_CHARS_SUFFIX_HOR + 1 +\
										INFO_CHARS)

# define DIVIDE_HOR_FIRST				(0)
# define DIVIDE_HOR_SECOND				(1 + CONTENTS_CHARS_PREFIX_VER +\
										CONTENTS_LINES_FOR_MEM +\
										CONTENTS_CHARS_SUFFIX_VER)



# define LINES_HOR 254
# define LINES_VER 68

#endif
