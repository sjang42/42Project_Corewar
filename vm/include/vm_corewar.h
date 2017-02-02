/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:15:18 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 16:15:20 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <op.h>

typedef struct	s_map
{
	char	*map;
	int		size_map;
	int		pc;
}				t_map;

# define LENGTH_MAGIC			4
# define LENGTH_PROG_SIZE		4
# define LENGTH_BEFORE_INST		LENGTH_MAGIC + PROG_NAME_LENGTH + 4\
								+ LENGTH_PROG_SIZE\
								+ COMMENT_LENGTH + 4


void			print_memory(const void *addr, size_t size);
int 			t_map_put_all(t_map *tmap, int fd[], int size);
t_map			*t_map_new(int size);
