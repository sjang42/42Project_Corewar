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

static int		t_cham_get_inst(t_inst *tinst, int prog_size, char *str)
{
	tinst->inst = (char*)malloc(sizeof(char) * prog_size);
	ft_memcpy(tinst->inst, str + LENGTH_BEFORE_INST, prog_size);
	tinst->size_inst = prog_size;
	tinst->mem_inst = prog_size;
	return (0);
}

static int		t_cham_get_file(t_file *tfile, char *fname)
{
	tfile->fname = ft_strdup(fname);
	tfile->fd = open(fname, O_RDONLY);
	if (tfile->fd < 0)
		ft_exit_error(NULL);
	return (0);
}

static int		t_cham_get_proc(t_proc *tproc, int num)
{
	t_proc	*new_tproc;

	new_tproc = t_proc_new(0, 0, num, NULL);
	ft_memcpy(tproc, new_tproc, sizeof(t_proc));
	return (0);
}

t_champion		*t_champion_new(char *fname, int num)
{
	t_champion	*tcham;
	char		*str;
	int			size_str;

	tcham = (t_champion*)malloc(sizeof(t_champion));
	tcham->number = num;
	t_cham_get_file(&(tcham->tfile), fname);
	size_str = ft_read_all(tcham->tfile.fd, &str);
	if (size_str == -1 || size_str < LENGTH_BEFORE_INST)
		ft_exit_error("Wrong file");
	vm_read_header(&(tcham->theader), tcham->tfile.fd, str, size_str);
	t_cham_get_inst(&(tcham->tinst), tcham->theader.prog_size, str);
	tcham->tproc = (t_proc*)malloc(sizeof(t_proc) * 5);
	tcham->mem_tproc = 5;
	tcham->num_tproc = 1;
	t_cham_get_proc(&(tcham->tproc[0]), num);
	free(str);
	return (tcham);
}
