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

# define CONTENTS_CHARS_PER_LINE		128
# define CONTENTS_LINES_FOR_MEM		MEM_SIZE / CHARS_PER_LINE

# define CONTENTS_CHARS_PREFIX_HOR		2
# define CONTENTS_CHARS_SUFFIX_HOR		2

# define CONTENTS_CHARS_PREFIX_VER		1
# define CONTENTS_CHARS_SUFFIX_VER		1

# define INFO_CHARS						56

# define LINES_HOR 254
# define LINES_VER 68


#endif
