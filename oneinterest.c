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

void oneinterest(int color){

	//Calling variables
	double invest,rate,period,weekfloat;		//Call the important floats,
	int weekinteger;				//Call the integer for counting weeks.
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1 = malloc(sizeof(*inv1)); //Call a struct for the investment as a pointer. (Thanks to Xen)

	//Preparing the Data-Collecting Windows
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
	WINDOW * calcwindowa = newwin(36,72,0,14);	//Displays values.
	WINDOW * calcwindowb = newwin(13,14,0,0);	//Displays controls.
	WINDOW * calcwindowc = newwin(3,14,13,0);	//Displays years.
	WINDOW * calcwindowd = newwin(4,14,16,0);	//Displays goto.
	WINDOW * calcwindowe = newwin(6,14,20,0);	//Displays find.
	
	wattron(calcwindowa,COLOR_PAIR(1)); wbkgd(calcwindowa,COLOR_PAIR(1));
	wattron(calcwindowb,COLOR_PAIR(1)); wbkgd(calcwindowb,COLOR_PAIR(1));
	wattron(calcwindowc,COLOR_PAIR(1)); wbkgd(calcwindowc,COLOR_PAIR(1));
	wattron(calcwindowd,COLOR_PAIR(1)); wbkgd(calcwindowd,COLOR_PAIR(1));
	wattron(calcwindowe,COLOR_PAIR(1)); wbkgd(calcwindowe,COLOR_PAIR(1));
	box(calcwindowa,0,0); box(calcwindowb,0,0); box(calcwindowc,0,0);
	box(calcwindowd,0,0); box(calcwindowe,0,0);
	keypad(calcwindowb,true);

	//Page System Initialization
	int currentpage = 1;			//The current page. 
	int choice = 0;				//Used to select pages.
	int yearcount = 1;
	int specialweek = 0;
	double findweek = 0;

	//Getting our windows ready
	mvwprintw(calcwindowb,1,2,"UP + DOWN");
	mvwprintw(calcwindowb,2,2,"Scroll");
	mvwprintw(calcwindowb,4,2,"RETURN");
	mvwprintw(calcwindowb,5,2,"Exits");
	mvwprintw(calcwindowb,7,2,"G");
	mvwprintw(calcwindowb,8,2,"Goto");
	mvwprintw(calcwindowb,10,2,"F");
	mvwprintw(calcwindowb,11,2,"Find");
	
	mvwprintw(calcwindowc,1,1,"Year:");
	
	mvwprintw(calcwindowd,1,1,"Goto Week:");
	
	mvwprintw(calcwindowe,1,1,"Find Week:");
	mvwprintw(calcwindowe,2,1,"$");
	mvwprintw(calcwindowe,3,1,"Week:");
	
	wrefresh(calcwindowa); wrefresh(calcwindowb);
	wrefresh(calcwindowc); wrefresh(calcwindowd);
	wrefresh(calcwindowe);

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
			if(weekinteger < 52){	//Added because the goto/find features skip the natural decrement process.
				yearcount = 0;	
				mvwprintw(calcwindowc,1,7,"%d  ",yearcount);
				wrefresh(calcwindowc);
			}
			
			//Year notification system
			if(weekinteger % 52 == 0){				//If our Week # is a multiple of 52...
				yearcount = weekfloat / 52;			//We define our Year #.
				mvwprintw(calcwindowc,1,7,"%d  ",yearcount);	//Print the new Year #, then we tell
				wattron(calcwindowa,A_REVERSE);			//calcwindowa to print the next calc
				wrefresh(calcwindowc);				//with the A_REVERSE attr.
			}

			//Week highlight system
			if(weekinteger == specialweek){			//If our week is the 'special week',
				wattron(calcwindowa,A_REVERSE);		//Print with 'A_REVERSE',
				specialweek = 0;			//And make our special week 0.
			}

			inv1->returns = interestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf",weekinteger,inv1->returns);
			wattroff(calcwindowa,A_REVERSE);
			weekinteger++; weekshift++;
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

		if(choice == 'g'){					//Developed after the 'find week' feature.
			wrefresh(calcwindowd);				//See below for details.
			echo();
			mvwscanw(calcwindowd,2,1,"%d",&specialweek);
			currentpage = weekfind(specialweek);
			wrefresh(calcwindowd);
			mvwprintw(calcwindowd,2,1,"            ");
			noecho();
		}

		if(choice == 'f'){					//If we press the 'f' key,
			wrefresh(calcwindowe);				//Used to clear the input/output from last use.
			echo();						//Turn on echo so the user can see input,
			mvwscanw(calcwindowe,2,2,"%lf",&findweek);	//Take the user's input.
			findweek = interestfind(findweek,inv1->invest,inv1->rate,inv1->period);
			mvwprintw(calcwindowe,4,1,"%lf",findweek);	//Display the 'x' value to get the benchmark.
			specialweek = findweek;				//Make our 'specialweek' equal to that 'x' value.
			currentpage = weekfind(findweek);		//Define the current page using weekfind.
			wrefresh(calcwindowe);				//Refresh window and restart with new currentpage.
			mvwprintw(calcwindowe,2,2,"           ");	//Clears input and output.
			mvwprintw(calcwindowe,4,1,"            ");
			noecho();
		}
	}
	free(inv1);
	clear();
	endwin();
	return 0;
}
