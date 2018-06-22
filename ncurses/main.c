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
#include <stdio.h>
// #include <vm_display.h>
#include <ncurses.h>                                                         
#include <stdbool.h>                                                                                            
                                                                            
int main(void)
{
    WINDOW *win;
    WINDOW *win2;
    WINDOW *win3;
    int i;
    
    win = initscr();

    win2 = newwin(50, 50, 0, 0);
    win3 = newwin(50, 50, 0, 60);
    wborder(win2, '*', '*','*','*','*','*','*', '*');
    wborder(win3, '*', '*','*','*','*','*','*', '*');
    wrefresh(win2);
    wrefresh(win3);

    mvwprintw(win2, 5, 5, "%d", can_change_color());
    // init_color(1, 255, 255, 0);

    init_pair(1, COLOR_YELLOW, COLOR_RED);
    start_color();
    attron(COLOR_PAIR(1));
    mvwprintw(win, 5, 5, "hi");
    refresh();
    attroff(COLOR_PAIR(1));

    wgetch(win2);
    endwin();
    return (0);
}

















