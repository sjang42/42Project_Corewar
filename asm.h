/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:12 by sjang             #+#    #+#             */
/*   Updated: 2017/01/30 12:16:14 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "./op/op.h"

typedef struct	s_strs
{
	char	**strarr;
	int		size_mem;
	int		size_strarr;
}				t_strs;
enum
{
	LIVE = 1,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
};

#define T_INST					16

t_strs		*strs_new(size_t size_mem);
int			strs_addone(t_strs *strs, char *str);

t_strs		*file_to_strs(int fd);
header_t	*get_header(t_strs *strs);

void		ft_remove_overlap(char **str, char ch);
int			ft_endian_ltob(void *src, size_t size);
void		ft_destroy_strsplit(char **str);

int			switch_inst(char *str);
int			switch_type(char *str);