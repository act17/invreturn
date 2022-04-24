#include <ncurses.h>
#include <stdlib.h>
#include "interesttools.h"



struct investment{	//The investment struct
	double invest;
	double rate;
	double period;
	double returns;
};



//Two Investments		Note that this will have few comments; see 'oneintrest' function below.
int twointerest(){

	
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

	init_pair(1,COLOR_CYAN,COLOR_CYAN);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);

	wbkgd(stdscr, COLOR_PAIR(1));
	wattron(investwindow,COLOR_PAIR(2)); wbkgd(investwindow,COLOR_PAIR(2));
	wattron(ratewindow,COLOR_PAIR(2)); wbkgd(ratewindow,COLOR_PAIR(2));
	wattron(periodwindow,COLOR_PAIR(2)); wbkgd(periodwindow,COLOR_PAIR(2));

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
	WINDOW * calcwindowc = newwin(3,14,256,0);

	wattron(calcwindowa,COLOR_PAIR(2)); wbkgd(calcwindowa,COLOR_PAIR(2));
	wattron(calcwindowb,COLOR_PAIR(2)); wbkgd(calcwindowb,COLOR_PAIR(2));

	box(calcwindowa,0,0); box(calcwindowb,0,0);

	keypad(calcwindowb,true);

	int currentpage = 1; 
	int choice = 0;

	mvwprintw(calcwindowb,1,2,"Use the UP");
	mvwprintw(calcwindowb,2,2,"and DOWN");
	mvwprintw(calcwindowb,3,2,"arrow keys");
	mvwprintw(calcwindowb,4,2,"to scroll");
	wrefresh(calcwindowa); wrefresh(calcwindowb);


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
				int yearcount = weekfloat / 52;

				if(weekshift > 5)
					mvwin(calcwindowc,weekshift + 1,0);
				else
					mvwin(calcwindowc,6,0);
				box(calcwindowc,0,0);

				wattron(calcwindowc,COLOR_PAIR(2));
				wbkgd(calcwindowc,COLOR_PAIR(2));

				if(weekinteger == 52)
					mvwprintw(calcwindowc,1,1,"1 Year");
				else
					mvwprintw(calcwindowc,1,1,"%d Years",yearcount);

				wattron(calcwindowa,A_REVERSE);
				wrefresh(calcwindowc);
				wbkgd(calcwindowc,COLOR_PAIR(1));
				wclear(calcwindowc);
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
		wrefresh(calcwindowc);
		if(choice == 10)
			break;
	}


	endwin();
	return 0;
}



//One Investment
int oneinterest(){

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

	init_pair(1,COLOR_CYAN,COLOR_CYAN);		//Color-pair 1 is just a background of Cyan.
	init_pair(2,COLOR_BLACK,COLOR_WHITE);		//Color-pair 2 is a nice combo of Black and White (Grey)

	wbkgd(stdscr, COLOR_PAIR(1));
	wattron(investwindow,COLOR_PAIR(2)); wbkgd(investwindow,COLOR_PAIR(2));
	wattron(ratewindow,COLOR_PAIR(2)); wbkgd(ratewindow,COLOR_PAIR(2));
	wattron(periodwindow,COLOR_PAIR(2)); wbkgd(periodwindow,COLOR_PAIR(2));

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
	WINDOW * calcwindowc = newwin(3,14,256,0);
	
	wattron(calcwindowa,COLOR_PAIR(2)); wbkgd(calcwindowa,COLOR_PAIR(2));
	wattron(calcwindowb,COLOR_PAIR(2)); wbkgd(calcwindowb,COLOR_PAIR(2));
	
	box(calcwindowa,0,0); box(calcwindowb,0,0);
	keypad(calcwindowb,true);

	//Page System Initialization
	int currentpage = 1;			//The current page. 
	int choice = 0;				//Used to select pages.

	//Getting our windows ready
	wrefresh(calcwindowa); wrefresh(calcwindowb);
	mvwprintw(calcwindowb,1,2,"Use the UP");
	mvwprintw(calcwindowb,2,2,"and DOWN");
	mvwprintw(calcwindowb,3,2,"arrow keys");
	mvwprintw(calcwindowb,4,2,"to scroll");


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
			if(weekinteger % 52 == 0){						//If our Week # is a multiple of 52...
				int yearcount = weekfloat / 52;					//Our year is the Week # divided by 52.

				if(weekshift > 5)						//If the window won't overlap calcwindowb,
					mvwin(calcwindowc,weekshift + 1,0);			//We take this window and shift it into
												//place.
				else								//Otherwise we move the window to the
					mvwin(calcwindowc,6,0);					//'default' position.
				box(calcwindowc,0,0);						

				wattron(calcwindowc,COLOR_PAIR(2));				//After making the window a box, we fill
				wbkgd(calcwindowc,COLOR_PAIR(2));				//it with color.

				if(weekinteger == 52)						//If it's just one year, then we use the
					mvwprintw(calcwindowc,1,1,"1 Year");			//singular 'year'.
				else
					mvwprintw(calcwindowc,1,1,"%d Years",yearcount);	//Otherwise, we use the multiple 'years'.

				wattron(calcwindowa,A_REVERSE);					//Tell calcwindowa to print the next calc
				wrefresh(calcwindowc);						//with the 'A_REVERSE' attribute.
				wbkgd(calcwindowc,COLOR_PAIR(1));				//Clear the window's colors,
				wclear(calcwindowc);						//Then we wait to delete the window.
			}


			inv1->returns = interestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf",weekinteger,inv1->returns);
			wattroff(calcwindowa,A_REVERSE);
			weekinteger++; weekshift++;;
			weekfloat = weekinteger;
		}
		
		wrefresh(calcwindowa);
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
		wrefresh(calcwindowc);				//Deletes the window, see above.
		if(choice == 10)				//If we press the enter key,
			break;					//Then exit.
	}

	endwin();						//And terminate the program.
	return 0;
}



//Main
int main(){

	initscr();
	cbreak();
	noecho();
	start_color();


	//Error Check
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);		//Program needs at least 36 y-axis units and 72 x-axis units.
	if(yMax < 36 || xMax < 86){		//If window cannot meet those requirements it stops and prints an error code.
		endwin();
		printf("\nError!\nError Code:		01\nWindow Dimensions too small!");
		printf("\nyMax = %d			xMax = %d",yMax,xMax);
		printf("\nyMax must be at least 36.	xMax must be at least 86.");
		return 1;
	}

	
	//Initializing the screen.
	WINDOW * titlewin = newwin(4,86, 0, 0);
	WINDOW * choicewin = newwin(5,86, 5, 0);
	WINDOW * infowin = newwin(5,86, 11, 0);

	init_pair(1,COLOR_CYAN,COLOR_CYAN);		//Color-pair 1 is just a background of Cyan.
	init_pair(2,COLOR_BLACK,COLOR_WHITE);		//Color-pair 2 is a nice combo of Black and White (Grey)

	wbkgd(stdscr, COLOR_PAIR(1));
	wattron(titlewin,COLOR_PAIR(2)); wbkgd(titlewin,COLOR_PAIR(2));
	wattron(choicewin,COLOR_PAIR(2)); wbkgd(choicewin,COLOR_PAIR(2));
	wattron(infowin,COLOR_PAIR(2)); wbkgd(infowin,COLOR_PAIR(2));

	box(titlewin, 0, 0); box(choicewin, 0, 0); box(infowin, 0, 0);
	
	mvwprintw(titlewin, 1, 2, "ACT's Investment-Return Calculator");
	mvwprintw(titlewin, 2, 15, "Version 2.2");
	mvwprintw(choicewin, 1, 2, "1 or 2 investments?");
	mvwprintw(infowin, 1, 2, "Copyright 2022 ACT");
	mvwprintw(infowin, 2, 2, "Licensed under the GNU GPL 3.0");
	mvwprintw(infowin, 3, 2, "https://github.com/act17/invreturn");

	refresh(); wrefresh(titlewin); wrefresh(choicewin); wrefresh(infowin);
	keypad(choicewin, true);
	

	int choice;
	int highlight = 1;


	//Selection Menu
	while(1){

		for(int i = 1; i < 3; i++){
			if(i == highlight)
				wattron(choicewin, A_REVERSE);
			mvwprintw(choicewin, i+1, 10, "%d", i);
			wattroff(choicewin, A_REVERSE);
		}


		choice = wgetch(choicewin);
		switch(choice)
		{
			case KEY_UP:
				if(highlight == 1)
					break;
				highlight--;
				break;
			case KEY_DOWN:
				if(highlight == 2)
					break;
				highlight++;
				break;
			default:
				break;
		}


		if(choice == 10)
			break;
	}
	

	//Opening the functions to calculate one or two interests
	clear();
	endwin();

	if(highlight == 1)
		oneinterest();
	if(highlight == 2)
		twointerest();


	return 0;
}
