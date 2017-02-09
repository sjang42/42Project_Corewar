/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:12:58 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 18:13:00 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <badguy.h>
#include <ncurses.h>
#include <unistd.h>

int main(void)
{
	WINDOW *win;
	int i;
	
	win = initscr();

	if (has_colors())
	{
		start_color();
		mvprintw(5, 5, "There are %d COLORS, and %d COLOR_PAIRS available",
				COLORS, COLOR_PAIRS);
		refresh();
	}
	init_color(18, 255, 255, 0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_GREEN);
	init_pair(3, COLOR_GREEN, COLOR_RED);
	init_pair(4, COLOR_YELLOW, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(7, COLOR_CYAN, COLOR_WHITE);
	init_pair(8, 1, 1);
	i = 0;
	while (i < 9)
	{
		attroff(A_BOLD);
		attrset(COLOR_PAIR(i));
		mvprintw(5 + i, 5, "Color pair %d", i);
		attrset(COLOR_PAIR(i) | A_BOLD);
		mvprintw(5 + i, 25, "Bold color pair %d", i);
		refresh();
		usleep(50000);
		i++;
	}
	getch();
	endwin();
	return (0);
}
