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

#include <libft.h>
#include <vm_t_header.h>
#include <vm_t_champion.h>
#include <stdio.h>//

int				vm_get_inst(t_inst *tinst, int prog_size, char *str)
{
	tinst->inst = (char*)malloc(sizeof(char) * prog_size);
	ft_memcpy(tinst->inst, str + LENGTH_BEFORE_INST, prog_size);
	tinst->size_inst = prog_size;
	tinst->mem_inst = prog_size;
	return (0);
}

int				vm_get_file(t_file *tfile, char *fname)
{
	tfile->fname = ft_strdup(fname);
	tfile->fd = open(fname, O_RDONLY);
	if (tfile->fd < 0)
		ft_exit_error(NULL);
	return (0);
}

int				vm_get_proc(t_proc *tproc, int num)
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
	vm_get_file(&(tcham->tfile), fname);
	size_str = ft_read_all(tcham->tfile.fd, &str);
	if (size_str == -1 || size_str < LENGTH_BEFORE_INST)
		ft_exit_error("Wrong file");
	vm_read_header(&(tcham->theader), tcham->tfile.fd, str, size_str);
	vm_get_inst(&(tcham->tinst), tcham->theader.prog_size, str);
	tcham->tproc = (t_proc*)malloc(sizeof(t_proc) * 1);
	vm_get_proc(&(tcham->tproc[0]), num);
	tcham->num_tproc = 1;
	free(str);
	return (tcham);
}

void			t_champion_showinfo(t_champion *tcham)
{
	int i;
	int j;
	int num;

	ft_putstr("Champion Number :\t");
	ft_putnbr(tcham->number);
	ft_putstr("\n");
	
	ft_putstr("Filename :\t\t");
	ft_putstr(tcham->tfile.fname);
	ft_putstr("\n");
	
	ft_putstr("Size :\t\t\t");
	ft_putnbr(tcham->theader.prog_size);
	ft_putstr("\n");
	
	ft_putstr("Name :\t\t\t");
	ft_putstr(tcham->theader.prog_name);
	ft_putstr("\n");
	
	ft_putstr("Comment :\t\t");
	ft_putstr(tcham->theader.comment);
	ft_putstr("\n");
	ft_putstr("\n");

	i = 0;
	while (i < tcham->num_tproc)
	{
		ft_putstr("proc num : ");
		ft_putnbr(i);
		ft_putstr("\n");
		ft_putstr("pc :\t");
		ft_putnbr(tcham->tproc[i].pc);
		ft_putstr("\n");
		ft_putstr("carry :\t");
		ft_putnbr(tcham->tproc[i].carry);
		ft_putstr("\n");
		j = 0;
		while (j < REG_NUMBER)
		{
			ft_memcpy(&num, (tcham->tproc[i]).registry[j], REG_SIZE);
			ft_putstr("[r");
			ft_putnbr(j + 1);
			ft_putstr("] : ");
			ft_putnbr(num);
			ft_putstr(" ");
			j++;
		}
		i++;
	}
	ft_putstr("\n\n");
}

void			t_champion_destroy(t_champion **tcham)
{
	int i;

	free((*tcham)->tfile.fname);
	free((*tcham)->tinst.inst);
	i = 0;
	while (i < (*tcham)->num_tproc)
	{
		t_proc_destroy(&((*tcham)->tproc[i]));
		i++;
	}
	free(*tcham);
	*tcham = NULL;
}

void			ft_champion_destroy_exit(t_champion **tcham)
{
	t_champion_destroy(tcham);
	ft_exit_error(NULL);
}
