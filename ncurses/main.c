/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 14:53:11 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 14:53:12 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <badguy.h>
#include <ncurses.h>
#include <unistd.h>

void	draw_repeat_ch_hor(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x, y + i);
		waddch(win, ch);
		// refresh();
		// usleep(50000);
		i++;
	}
}

void	draw_repeat_ch_ver(WINDOW *win, char ch, int size, int x, int y)
{
	int i;

	i = 0;
	while (i < size)
	{
		wmove(win, x + i, y);
		waddch(win, ch);
		i++;
	}
}


int main(void)
{
	WINDOW *win;
	int i;
	
	win = initscr();
	draw_repeat_ch_hor(win, '*', 254, 0, 0);
	draw_repeat_ch_hor(win, '*', 254, 67, 0);
	draw_repeat_ch_ver(win, '*', 66, 1, 0);
	draw_repeat_ch_ver(win, '*', 66, 1, 195);
	draw_repeat_ch_ver(win, '*', 66, 1, 253);
	refresh();



	getch();
	endwin();
	return (0);
}
