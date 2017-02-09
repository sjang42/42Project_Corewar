/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnswerIt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:51:03 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 16:51:05 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <badguy.h>
#include <ncurses.h>
#include <unistd.h>

#define PW_LEN 25
#define ID_LEN 256

int main(void)
{
	WINDOW *win;
	char	Welcome[] = "Welcome to AnswerIt!";
	char 	user_id[ID_LEN + 1];
	char 	user_pw[PW_LEN + 1];
	int		i;
	int 	num_q;
	int		point;

	num_q = 1;
	point = 0;
	win = initscr();

	box(win, '*', '*');

	move(LINES / 12 * 3, COLS / 8 * 4 - (strlen(Welcome) / 2));
	printw("%s", Welcome);
	getch();
	clear();
	box(win, '*', '*');

	move(LINES / 12 * 3, COLS / 8 * 4);
	printw("Question %d", num_q);

	move(LINES / 12 * 4, COLS / 8 * 3);
	printw("%s", "Q        : What is the best hero ever?");

	move(LINES / 12 * 4 + 2, COLS / 8 * 3);
	printw("%s", "Password : ");
	refresh();

	cbreak();
	noecho();
	bzero(user_pw, PW_LEN + 1);
	i = 0;
	while (i < PW_LEN)
	{
		user_pw[i] = getch();
		move(LINES / 12 * 4 + 2, COLS / 8 * 3 + 11 + i);
		if (user_pw[i] == 127)
		{
			if (i == 0)
				continue;
			move(LINES / 12 * 4 + 2, COLS / 8 * 3 + 11 + i - 1);
			addch(' ');
			move(LINES / 12 * 4 + 2, COLS / 8 * 3 + 11 + i - 1);
			refresh();
			i--;
			continue;
		}
		if (user_pw[i] != '\n')
			addch('*');
		refresh();
		if (user_pw[i] == '\n')
		{
			user_pw[i] = '\0';
			break;
		}
		i++;
	}

	nocbreak();
	echo();
	clear();
	box(win, '*', '*');
	

	move(LINES / 12 * 4 + 2, COLS / 8 * 3);
	if (!strcmp(user_pw, REAL_PW))
	{
		printw("%s", "You are right!");
		move(LINES / 12 * 4 + 4, COLS / 8 * 3);
		printw("You got a point.");
		point++;
	}
	else
	{
		printw("%s", "Wrong..!");
		move(LINES / 12 * 4 + 4, COLS / 8 * 3);
		printw("Are you serious? How '%s' can be the best hero?", user_pw);
	}

	move(LINES / 12 * 4 + 8, COLS / 8 * 3);

	printw("Your Point : %d", point);

	refresh();
	getch();

	endwin();
	return (0);
}