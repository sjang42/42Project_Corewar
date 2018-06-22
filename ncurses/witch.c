/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   witch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:02:12 by sjang             #+#    #+#             */
/*   Updated: 2017/02/07 16:02:13 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <ncurses.h>
#include <unistd.h>


int main(void)
{
    WINDOW *win;
    char witch_one[] = " First Witch  ";
    char witch_two[] = " Second Witch ";
    char *scan_ptr;

    win = initscr();

    attron(A_STANDOUT);
    box(win, '*', '*');
    attroff(A_STANDOUT);


    move(2, 15);
    printw("%s", "Thunder and Lightning");
    refresh();
    usleep(50000);

    move(5, 15);
    attron(A_BOLD);
    printw("%s", "Thunder and Lightning");
    attroff(A_BOLD);
    refresh();
    usleep(50000);

    move(8, 15);
    attron(A_STANDOUT);
    printw("%s", "Thunder and Lightning");
    attroff(A_STANDOUT);
    refresh();
    usleep(50000);

    move(11, 15);
    attron(A_DIM);
    printw("%s", "Thunder and Lightning");
    attroff(A_DIM);
    refresh();
    usleep(50000);



    attron(A_DIM);
    scan_ptr = witch_one + strlen(witch_one) - 1;
    while(scan_ptr != witch_one)
    {
        move(10, 10);
        insch(*scan_ptr);
        scan_ptr--;
        refresh();
        usleep(50000);
    }
    scan_ptr = witch_two + strlen(witch_two) - 1;
    while(scan_ptr != witch_two)
    {
        move(13, 10);
        insch(*scan_ptr);
        scan_ptr--;
        refresh();
        usleep(50000);
    }
    attroff(A_DIM);
    refresh();



    move(LINES - 1, COLS - 1);
    sleep(10);
    endwin();
    return (0);
}