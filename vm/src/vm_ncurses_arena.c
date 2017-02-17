/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_arena.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 21:18:07 by sjang             #+#    #+#             */
/*   Updated: 2017/02/15 21:18:09 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm_ncurses.h>

void			ncur_erase_termsays(WINDOW *win)
{
	int i;

	i = 0;
	wattron(win, COLOR_PAIR(7) | A_BOLD);
	wmove(win, TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN);
	while (i < 181)
	{
		wprintw(win, " ");
		i++;
	}
	wrefresh(win);
	wattroff(win, COLOR_PAIR(7) | A_BOLD);
}

void			ncur_show_termsays(WINDOW *win_arena)
{
	wattron(win_arena, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win_arena, TERM_SAYS_Y, TERM_SAYS_X, TERM_SAYS_MASSAGE);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(7) | A_BOLD);
}

void			ncur_show_live(WINDOW *win_arena, int idx_cham, int live_cham)
{
	static int idx = 0;

	ncur_erase_termsays(win_arena);
	if (idx >= 10)
		idx = 0;
	if (idx % 2 == 0)
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD);
	else
		wattron(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	mvwprintw(win_arena,
			TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN,
			"A process shows that player %d is alive", live_cham);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(idx_cham + 1) | A_BOLD | A_REVERSE);
	idx++;
}

void			ncur_show_winner(WINDOW *win_arena, t_arena *tarena)
{
	int			idx_cham;
	int			idx_winner;
	long long	most_last_live;

	idx_cham = 0;
	idx_winner = 0;
	while (idx_cham < tarena->num_cham)
	{
		if (tarena->tcham[idx_cham]->last_live >= most_last_live)
		{
			idx_winner = idx_cham;
			most_last_live = tarena->tcham[idx_cham]->last_live;
		}
		idx_cham++;
	}
	ncur_erase_termsays(win_arena);
	wattron(win_arena, COLOR_PAIR(idx_winner + 1) | A_BOLD | A_REVERSE);
	mvwprintw(win_arena,
			TERM_SAYS_Y, TERM_SAYS_X + TERM_SAYS_MASSAGE_LEN,
			"Player %d (%s) won",
			tarena->tcham[idx_winner]->number,
			tarena->tcham[idx_winner]->theader.prog_name);
	wrefresh(win_arena);
	wattroff(win_arena, COLOR_PAIR(idx_winner + 1) | A_BOLD | A_REVERSE);
}
