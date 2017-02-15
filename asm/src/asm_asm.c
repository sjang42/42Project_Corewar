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
		return (-1);
	out_name = (char*)malloc(ft_strlen(file_origin) + 3);
	ft_strcpy(out_name, file_origin);
	tmp = ft_strstr(out_name, ".s");
	if (tmp)
		*tmp = 0;
	ft_strcat(out_name, ".jex");
	// ft_strcat(out_name, ".cor");
	fd_write = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	free(out_name);
	if (fd_write < 0)
		return (-1);
	return (fd_write);
}

void		destroy_process(t_process process)
{
	strs_destroy(process.tstrs);
	t_label_destroy(process.tlabel);
	t_inst_destroy(&(process.tinst));
	free(process.header);
}

int				ft_asm(char *file)
{
	int			fd_read;
	int			fd_write;
	t_process	process;

	fd_read = open(file, O_RDONLY);
	if (fd_read == -1)
		ft_exit_error("Failed to open file");
	process.tstrs = file_to_strs(fd_read);
	process.tlabel = get_label(process.tstrs);
	process.tinst = get_inst(process.tstrs, process.tlabel);
	process.header = get_header(process.tstrs);
	process.zero = 0;
	process.header->prog_size = process.tinst->size_inst;
	ft_endian_ltob(&(process.header->prog_size), 4);
	if (process.tinst->size_inst > CHAMP_MAX_SIZE)
	{
		destroy_process(process);
		ft_exit_error("Champion size is too big");
	}
	fd_write = get_fd_write(file);
	if (fd_write < 0)
	{
		destroy_process(process);
		ft_exit_error("Failed to make file");
	}
	write(fd_write, &(process.header->magic), 4);
	write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
	write(fd_write, &(process.zero), 4);
	write(fd_write, &(process.header->prog_size), 4);
	write(fd_write, process.header->comment, COMMENT_LENGTH);
	write(fd_write, &(process.zero), 4);
	write(fd_write, process.tinst->inst, process.tinst->size_inst);
	destroy_process(process);
	return (0);
}

// // 실험용.. 실전에선 지우고 밑에 ft_asm함수 쓰길.
// int				ft_asm(char *file)
// {
// 	int			fd_read;
// 	int			fd_write;
// 	t_process	process;
// 	char 		ins[] = {	2,	0x9f, 0,0,0,0,	3,
// 							// 3,	0x90, 9,0,0,3, 0,
// 							// 4,	0xa8, 0,0,0,0, 0,0,0,0, 0,0,0,0,
// 							2,	0x20, 0,0,0,0,
// 							9,	0,0};

// 	fd_read = open(file, O_RDONLY);

// 	process.tstrs = file_to_strs(fd_read);
// 	process.header = get_header(process.tstrs);
// 	process.tlabel = get_label(process.tstrs);
// 	process.tinst = get_inst(process.tstrs, process.tlabel);
// 	process.zero = 0;

// 	// process.header->prog_size = process.tinst->size_inst;
// 	process.header->prog_size = sizeof(ins);//
// 	ft_endian_ltob(&(process.header->prog_size), 4);
// 	fd_write = get_fd_write(file);
// 	write(fd_write, &(process.header->magic), 4);
// 	write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
// 	write(fd_write, &(process.zero), 4);
// 	write(fd_write, &(process.header->prog_size), 4);

// 	write(fd_write, process.header->comment, COMMENT_LENGTH);
// 	write(fd_write, &(process.zero), 4);

// 	write(fd_write, ins, sizeof(ins));
// 	// write(fd_write, process.tinst->inst, process.tinst->size_inst);
// 	return (0);
// }

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

// 	// write(fd_write, process.tinst->inst, process.tinst->size_inst);
// 	// ft_print_memory(process.tinst->inst, process.tinst->size_inst);

// 	write(fd_write, &(process.header->magic), 4);
// 	write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
// 	write(fd_write, &(process.zero), 4);
// 	write(fd_write, &(process.header->prog_size), 4);
// 	write(fd_write, process.header->comment, COMMENT_LENGTH);
// 	write(fd_write, &(process.zero), 4);
// 	write(fd_write, process.tinst->inst, process.tinst->size_inst);
// 	return (0);
// }
