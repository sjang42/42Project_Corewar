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

static int      get_fd_write(char *file_origin)
{
    char        *tmp;
    char        *out_name;
    int         fd_write;

    if (!file_origin)
        return (-1);
    out_name = (char*)malloc(ft_strlen(file_origin) + 3);
    ft_strcpy(out_name, file_origin);
    tmp = ft_strstr(out_name, ".s");
    if (tmp)
        *tmp = 0;
    ft_strcat(out_name, ".jex");
    fd_write = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    free(out_name);
    if (fd_write < 0)
        return (-1);
    return (fd_write);
}

static void     destroy_process(t_process process)
{
    strs_destroy(process.tstrs);
    t_label_destroy(process.tlabel);
    t_inst_destroy(&(process.tinst));
    free(process.header);
}

static void     read_process(t_process *process, int fd_read)
{
    process->tstrs = file_to_strs(fd_read);
    process->tlabel = get_label(process->tstrs);
    process->tinst = get_inst(process->tstrs, process->tlabel);
    process->header = get_header(process->tstrs);
    process->zero = 0;
    process->header->prog_size = process->tinst->size_inst;
    ft_endian_convert(&(process->header->prog_size), 4);
}

static void     write_process(t_process process, int fd_write)
{
    write(fd_write, &(process.header->magic), 4);
    write(fd_write, process.header->prog_name, PROG_NAME_LENGTH);
    write(fd_write, &(process.zero), 4);
    write(fd_write, &(process.header->prog_size), 4);
    write(fd_write, process.header->comment, COMMENT_LENGTH);
    write(fd_write, &(process.zero), 4);
    write(fd_write, process.tinst->inst, process.tinst->size_inst);
}

int             ft_asm(char *file)
{
    int         fd_read;
    int         fd_write;
    t_process   process;

    fd_read = open(file, O_RDONLY);
    if (fd_read == -1)
        ft_exit_error("Failed to open file");
    read_process(&process, fd_read);
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
    write_process(process, fd_write);
    destroy_process(process);
    return (0);
}
