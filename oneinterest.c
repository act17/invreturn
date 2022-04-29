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

int oneinterest(int color){

	//Calling variables
	double invest,rate,period,weekfloat;		//Call the important floats,
	int weekinteger,weekcounter;			//Call the integers for counting weeks,
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1 = malloc(sizeof(*inv1)); //Call a struct for the investment as a pointer. (Thanks to Xen)

	//Preparing the Data-Collecting Windows
	initscr();
	echo();
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * investwindow = newwin(4,86,0,0); WINDOW * ratewindow = newwin(4,86,4,0);
	WINDOW * periodwindow = newwin(5,86,8,0);

	init_pair(1,COLOR_BLACK,COLOR_WHITE);		//See Line 40 of invreturn.c
	init_pair(2,COLOR_CYAN,COLOR_CYAN);
	init_pair(3,COLOR_GREEN,COLOR_GREEN);
	init_pair(4,COLOR_MAGENTA,COLOR_MAGENTA);

	wbkgd(stdscr,COLOR_PAIR(color));
	wattron(investwindow,COLOR_PAIR(1)); wbkgd(investwindow,COLOR_PAIR(1));
	wattron(ratewindow,COLOR_PAIR(1)); wbkgd(ratewindow,COLOR_PAIR(1));
	wattron(periodwindow,COLOR_PAIR(1)); wbkgd(periodwindow,COLOR_PAIR(1));

	box(investwindow,0,0); box(ratewindow,0,0); box(periodwindow,0,0);
	
	//Printing in the Windows
	mvwprintw(investwindow,1,1,"Investment:");
	mvwprintw(ratewindow,1,1,"Rate Percent:");
	mvwprintw(periodwindow,1,1,"Annual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	mvwprintw(periodwindow,2,1,"Weeks in Period:");

	//Window Refreshing
	refresh();
	wrefresh(investwindow); wrefresh(ratewindow); wrefresh(periodwindow);


	//Getting the important information relating to the investment.
	mvwscanw(investwindow,2,1,"%lf",&invest);
	mvwscanw(ratewindow,2,1,"%lf",&rate);
	mvwscanw(periodwindow,3,1,"%lf",&period);

	//Calculating the Variables
	inv1->invest = invest;
	inv1->rate = (rate + 100) / 100;	//Convert the rate from a percent into a decimal for calculation.
	inv1->period = period;	
	
	//Clear && NoEcho && Refresh
	clear();
	noecho();
	refresh();


	//Preparing the Table of Values
	WINDOW * calcwindowa = newwin(36,72,0,14);
	WINDOW * calcwindowb = newwin(6,14,0,0);
	WINDOW * calcwindowc = newwin(3,14,6,0);
	
	wattron(calcwindowa,COLOR_PAIR(1)); wbkgd(calcwindowa,COLOR_PAIR(1));
	wattron(calcwindowb,COLOR_PAIR(1)); wbkgd(calcwindowb,COLOR_PAIR(1));
	wattron(calcwindowc,COLOR_PAIR(1)); wbkgd(calcwindowc,COLOR_PAIR(1));
	box(calcwindowa,0,0); box(calcwindowb,0,0); box(calcwindowc,0,0);						
	keypad(calcwindowb,true);

	//Page System Initialization
	int currentpage = 1;			//The current page. 
	int choice = 0;				//Used to select pages.
	int yearcount = 1;

	//Getting our windows ready
	mvwprintw(calcwindowb,1,2,"Use the UP");
	mvwprintw(calcwindowb,2,2,"and DOWN");
	mvwprintw(calcwindowb,3,2,"arrow keys");
	mvwprintw(calcwindowb,4,2,"to scroll");
	mvwprintw(calcwindowc,1,1,"Year: 1");
	wrefresh(calcwindowa); wrefresh(calcwindowb); wrefresh(calcwindowc);

	//Calculation Loop
	while(1){

		int weekshift = 0;								//Shifts the text down the Y axis
		weekinteger = 1 + (33 * (currentpage - 1));					//Defines what 'y' value we'll start at.
		weekfloat = weekinteger;							//Same here.
		wclear(calcwindowa);								//Used to clear out previous page data.
		box(calcwindowa,0,0);								//Nessicary to get the box back.
		mvwprintw(calcwindowa,1,1,"Week 0:		%lf",inv1->invest);		//Printed consistantly at top.

		for(int pageinteger = 33 * currentpage; pageinteger != 0 + (33 * (currentpage - 1)); pageinteger--)
		{


			//Year notification system
			if(weekinteger % 52 == 0){				//If our Week # is a multiple of 52...
				yearcount = weekfloat / 52;			//We define our Year #.
				mvwprintw(calcwindowc,1,7,"%d",yearcount);	//Print the new Year #, then we tell
				wattron(calcwindowa,A_REVERSE);			//calcwindowa to print the next calc
				wrefresh(calcwindowc);				//with the A_REVERSE attr.
			}


			inv1->returns = interestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf",weekinteger,inv1->returns);
			wattroff(calcwindowa,A_REVERSE);
			weekinteger++; weekshift++;;
			weekfloat = weekinteger;
		}
		
		wrefresh(calcwindowa); wrefresh(calcwindowc);
		choice = wgetch(calcwindowb);

		switch(choice)
		{
			case KEY_UP:				//Up Arrow Key is pressed
				if(currentpage == 1)		//If we're at the first page...
					break;			//Then don't bother.
				currentpage--;			//Otherwise; go up a page by lowering our page value.
				break;
			case KEY_DOWN:				//Down Arrow Key is pressed
				currentpage++;			//Go down a page by raising our page value.
				break;
			default:
				break;
		}
		if(choice == 10)				//If we press the enter key,
			break;					//Then exit.
	}
	clear();
	endwin();						//And terminate the program.
	return 0;
}
