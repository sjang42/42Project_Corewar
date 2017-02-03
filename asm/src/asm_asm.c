/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:25:45 by sjang             #+#    #+#             */
/*   Updated: 2017/02/01 15:25:46 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		get_fd_write(char *file_origin)
{
	char 		*tmp;
	char		*out_name;
	int			fd_write;

	if (!file_origin)
		ft_exit_error("Fail to make file");
	out_name = ft_strdup(file_origin);
	tmp = ft_strstr(out_name, ".s");
	if (tmp)
		*tmp = 0;
	ft_strcat(out_name, ".cor");
	fd_write = open(out_name, O_WRONLY | O_CREAT,
					S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd_write < 0)
		ft_exit_error("Fail to make file");
	return (fd_write);
}

//실험용.. 실전에선 지우고 밑에 ft_asm함수 쓰길.
int				ft_asm(char *file)
{
	int			fd_read;
	int			fd_write;
	t_process	process;
	char 		ins[] = {20, 02, 0x68, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c};

	fd_read = open(file, O_RDONLY);

	process.tstrs = file_to_strs(fd_read);
	process.header = get_header(process.tstrs);
	process.tlabel = get_label(process.tstrs);
	process.tinst = get_inst(process.tstrs, process.tlabel);
	process.zero = 0;

	// process.header->prog_size = process.tinst->size_inst;
	process.header->prog_size = sizeof(ins);//
	ft_endian_ltob(&(process.header->prog_size), 4);
	fd_write = get_fd_write(file);
	write(fd_write, &(process.header->magic), 4);
	write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
	write(fd_write, &(process.zero), 4);
	write(fd_write, &(process.header->prog_size), 4);

	write(fd_write, process.header->comment, COMMENT_LENGTH);
	write(fd_write, &(process.zero), 4);

	write(fd_write, ins, sizeof(ins));
	// write(fd_write, process.tinst->inst, process.tinst->size_inst);
	return (0);
}

// int				ft_asm(char *file)
// {
// 	int			fd_read;
// 	int			fd_write;
// 	t_process	process;

// 	fd_read = open(file, O_RDONLY);

// 	process.tstrs = file_to_strs(fd_read);
// 	process.header = get_header(process.tstrs);
// 	process.tlabel = get_label(process.tstrs);
// 	process.tinst = get_inst(process.tstrs, process.tlabel);
// 	process.zero = 0;
// 	process.header->prog_size = process.tinst->size_inst;
// 	ft_endian_ltob(&(process.header->prog_size), 4);
// 	fd_write = get_fd_write(file);
// 	write(fd_write, &(process.header->magic), 4);
// 	write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
// 	write(fd_write, &(process.zero), 4);
// 	write(fd_write, &(process.header->prog_size), 4);
// 	write(fd_write, process.header->comment, COMMENT_LENGTH);
// 	write(fd_write, &(process.zero), 4);
// 	write(fd_write, process.tinst->inst, process.tinst->size_inst);
// 	return (0);
// }


