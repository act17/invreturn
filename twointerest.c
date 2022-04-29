#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include "interesttools.h"

struct investment{	//The investment struct
	double invest;
	double rate;
	double period;
	double returns;
};

int twointerest(int color){

	
	double invest,rate,period,weekfloat;
	int weekinteger,weekcounter;
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1 = malloc(sizeof(*inv1));
	struct investment *inv2 = malloc(sizeof(*inv2));

	
	initscr();
	echo();
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * investwindow = newwin(4,86,0,0); WINDOW * ratewindow = newwin(4,86,4,0);
	WINDOW * periodwindow = newwin(5,86,8,0);

	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_CYAN,COLOR_CYAN);
	init_pair(3,COLOR_GREEN,COLOR_GREEN);
	init_pair(4,COLOR_MAGENTA,COLOR_MAGENTA);

	wbkgd(stdscr, COLOR_PAIR(color));
	wattron(investwindow,COLOR_PAIR(1));	wbkgd(investwindow,COLOR_PAIR(1));
	wattron(ratewindow,COLOR_PAIR(1));	wbkgd(ratewindow,COLOR_PAIR(1));
	wattron(periodwindow,COLOR_PAIR(1));	wbkgd(periodwindow,COLOR_PAIR(1));

	box(investwindow,0,0); box(ratewindow,0,0); box(periodwindow,0,0);

	mvwprintw(investwindow,1,1,"Investment 1:		Investment 2:");
	mvwprintw(ratewindow,1,1,"Rate Percent 1:	Rate Percent 2:");
	mvwprintw(periodwindow,1,1,"Annual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");

	mvwprintw(periodwindow,2,1,"Weeks in Period 1:	Weeks in Period 2:");
	refresh();
	wrefresh(investwindow); wrefresh(ratewindow); wrefresh(periodwindow);


	mvwscanw(investwindow,2,1,"%lf",&invest);
	mvwscanw(ratewindow,2,1,"%lf",&rate);
	mvwscanw(periodwindow,3,1,"%lf",&period);

	inv1->invest = invest;
	inv1->rate = (rate + 100) / 100;
	inv1->period = period;
	
	mvwscanw(investwindow,2,24,"		%lf",&invest);
	mvwscanw(ratewindow,2,24,"		%lf",&rate);
	mvwscanw(periodwindow,3,24,"		%lf",&period);

	inv2->invest = invest;
	inv2->rate = (rate + 100) / 100;
	inv2->period = period;

	
	clear();
	noecho();
	refresh();

	WINDOW * calcwindowa = newwin(36,72,0,14);
	WINDOW * calcwindowb = newwin(6,14,0,0);
	WINDOW * calcwindowc = newwin(3,14,6,0);

	wattron(calcwindowa,COLOR_PAIR(1)); wbkgd(calcwindowa,COLOR_PAIR(1));
	wattron(calcwindowb,COLOR_PAIR(1)); wbkgd(calcwindowb,COLOR_PAIR(1));
	wattron(calcwindowc,COLOR_PAIR(1)); wbkgd(calcwindowc,COLOR_PAIR(1));
	box(calcwindowa,0,0); box(calcwindowb,0,0); box(calcwindowc,0,0);

	keypad(calcwindowb,true);

	int currentpage = 1; 
	int choice = 0;
	int yearcount;

	mvwprintw(calcwindowb,1,2,"Use the UP");
	mvwprintw(calcwindowb,2,2,"and DOWN");
	mvwprintw(calcwindowb,3,2,"arrow keys");
	mvwprintw(calcwindowb,4,2,"to scroll");
	mvwprintw(calcwindowc,1,1,"Year: 1");
	wrefresh(calcwindowa); wrefresh(calcwindowb); wrefresh(calcwindowc);

	while(1){

		int weekshift = 0;
		weekinteger = 1 + (33 * (currentpage - 1));
		weekfloat = weekinteger;
		wclear(calcwindowa);
		box(calcwindowa,0,0);
		mvwprintw(calcwindowa,1,1,"Week 0:		%lf	%lf",inv1->invest,inv2->invest);
		wrefresh(calcwindowa);

		for(int pageinteger = 33 * currentpage; pageinteger != 0 + (33 * (currentpage - 1)); pageinteger--)
		{


			if(weekinteger % 52 == 0){
				yearcount = weekfloat / 52;
				mvwprintw(calcwindowc,1,7,"%d",yearcount);
				wattron(calcwindowa,A_REVERSE);
				wrefresh(calcwindowc);
			}


			inv1->returns = interestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			inv2->returns = interestcalc(inv2->invest,inv2->rate,inv2->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf	%lf",weekinteger,inv1->returns,inv2->returns);
			weekinteger++; weekshift++;;
			weekfloat = weekinteger;
			wattroff(calcwindowa,A_REVERSE);
			wrefresh(calcwindowa);
		}
		

		choice = wgetch(calcwindowb);
		switch(choice)
		{
			case KEY_UP:
				if(currentpage == 1)
					break;
				currentpage--;
				break;
			case KEY_DOWN:
				currentpage++;
				break;
			default:
				break;
		}
		if(choice == 10)
			break;
	}

	clear();
	endwin();
	return 0;
}
