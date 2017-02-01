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

#include <op.h>
#include <asm_t_strs.h>
#include <asm_t_label.h>
#include <asm_t_inst.h>

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

#define CODEBYTE_REG					0B01
#define CODEBYTE_DIR					0B10
#define CODEBYTE_IND					0B11

t_strs		*file_to_strs(int fd);
header_t	*get_header(t_strs *strs);
t_label		*get_label(t_strs *tstrs);

void		ft_remove_overlap(char **str, char ch);
int			ft_endian_ltob(void *src, size_t size);
void		ft_destroy_strsplit(char **str);

int			switch_inst(char *str);
int			switch_type(char *str);

int			is_register(char *str);
int			is_direct(char *str);
int			is_indirect(char *str);
int			is_label(char *str);

int			t_label_get_idx(t_label *tlabel, char const *name);

int			check_command(char *command, char **arg);
int			decide_num_byte(char *command, char *arg);
t_inst		*get_inst(t_strs *strs, t_label *tlabel);