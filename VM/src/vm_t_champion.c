/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_t_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 13:02:42 by sjang             #+#    #+#             */
/*   Updated: 2017/02/02 13:02:43 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_t_champion.h>

static int      t_cham_get_inst(t_inst *tinst, int prog_size, char *str)
{
    tinst->inst = (char*)malloc(sizeof(char) * prog_size);
    ft_memcpy(tinst->inst, str + LENGTH_BEFORE_INST, prog_size);
    tinst->size_inst = prog_size;
    tinst->mem_inst = prog_size;
    return (0);
}

static int      t_cham_get_file(t_file *tfile, char *fname)
{
    tfile->fname = ft_strdup(fname);
    tfile->fd = open(fname, O_RDONLY);
    if (tfile->fd < 0)
    {
        msg_error_store("Wrong file");
        return (-1);
    }
    return (0);
}

static int      t_cham_get_proc(t_proc **tproc, int num, int proc_num)
{
    *tproc = t_proc_new(0, 0, NULL, proc_num);
    // t_proc_put(tproc, 0, 0, NULL);
    // tproc->number = proc_num;
    (*tproc)->just_born = 0;
    num *= -1;
    ft_memcpy((*tproc)->registry[0], &(num), REG_SIZE);
    return (0);
}

t_champion      *t_champion_new(char *fname, int num, int color, int proc_num)
{
    t_champion  *tcham;
    char        *str;
    int         size_str;

    tcham = (t_champion*)malloc(sizeof(t_champion));
    ft_bzero(tcham, sizeof(t_champion));
    tcham->number = num;
    tcham->color = color;
    tcham->last_live = 0;
    tcham->current_live = 0;
    if (t_cham_get_file(&(tcham->tfile), fname) == -1)
    {
        t_champion_destroy(tcham);
        return (NULL);
    }
    size_str = ft_read_all(tcham->tfile.fd, &str);
    if (size_str == -1 || size_str < LENGTH_BEFORE_INST)
    {
        t_champion_destroy(tcham);
        msg_error_store("Size is wrong");
        return (NULL);
    }
    if (vm_read_header(&(tcham->theader), str, size_str) == -1)
    {
        t_champion_destroy(tcham);
        return (NULL);
    }
    t_cham_get_inst(&(tcham->tinst), tcham->theader.prog_size, str);
    tcham->tproc = (t_proc**)malloc(sizeof(t_proc*) * 15);
    tcham->mem_tproc = 15;
    tcham->num_tproc = 1;
    t_cham_get_proc(&(tcham->tproc[0]), num, proc_num);
    free(str);
    return (tcham);
}
