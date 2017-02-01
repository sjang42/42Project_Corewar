/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 17:42:01 by sjang             #+#    #+#             */
/*   Updated: 2017/01/28 17:42:02 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	show_label(t_label *tlabel)
{
	int i;

	i = 0;
	while (i < tlabel->size_label)
	{
		printf("i : name : %s, idx : %d\n",
			tlabel->label[i].name, tlabel->label[i].idx);
		i++;
	}
}

void	show_inst(t_inst *tinst)
{
	int i;

	i = 0;
	while (i < tinst->size_inst)
	{
		printf("%x ", (unsigned char)tinst->inst[i]);
		i++;
	}
}

int		main(int argc, char *argv[])
{
	int			fd;
	int			fd2;
	char		*out_name;
	char		*tmp;
	t_strs		*tstrs;
	header_t	*header;
	t_inst		*tinst;
	t_label		*tlabel;
	int			zero;

	fd = open(argv[1], O_RDONLY);
	tstrs = file_to_strs(fd);
	header = get_header(tstrs);
	tlabel = get_label(tstrs);
	tinst = get_inst(tstrs, tlabel);

	zero = 0;
	header->prog_size = tinst->size_inst;
	ft_endian_ltob(&(header->prog_size), 4);
	out_name = ft_strdup(argv[1]);
	tmp = ft_strstr(out_name, ".s");
	if (tmp)
		*tmp = 0;
	ft_strcat(out_name, ".cor");
	fd2 = open(out_name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	write(fd2, &(zero), 4);
	write(fd2, &(header->magic), 4);
	write(fd2, header->prog_name, PROG_NAME_LENGTH);
	write(fd2, &(header->prog_size), 4);
	write(fd2, header->comment, COMMENT_LENGTH);
	write(fd2, &(zero), 4);
	write(fd2, tinst->inst, tinst->size_inst);
	return (0);
}
