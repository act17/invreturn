#include <ncurses.h>
#include <stdlib.h>
#include "intresttools.h"

struct investment{	//The investment struct
	double invest;
	double rate;
	double period;
	double returns;
};




//Two Investments
int twointerest(){

	//Calling Data-Collecting Variables
	double invest,rate,period,weekfloat;
	int weekinteger,weekcounter;
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1 = malloc(sizeof(*inv1));
	struct investment *inv2 = malloc(sizeof(*inv2));

	//Preparing the Data-Collecting Windows
	initscr();
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * investwindow = newwin(4,xMax-12,yMax-36,6); WINDOW * ratewindow = newwin(4,xMax-12,yMax-32,6);
	WINDOW * periodwindow = newwin(5,xMax-12,yMax-28,6);
	box(investwindow,0,0); box(ratewindow,0,0); box(periodwindow,0,0);
	
	//Window Refreshing
	refresh();
	wrefresh(investwindow); wrefresh(ratewindow); wrefresh(periodwindow);

	//Printing the informational windows, and collecting our first investment info.
	mvwprintw(investwindow,1,1,"Investment 1:	Investment 2:");
	mvwscanw(investwindow,2,1,"%lf",&invest);
	mvwprintw(ratewindow,1,1,"Rate Percent 1:	Rate Percent 2:");
	mvwscanw(ratewindow,2,1,"%lf",&rate);
	mvwprintw(periodwindow,1,1,"Annual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	mvwprintw(periodwindow,2,1,"Weeks in Period 1:	Weeks in Period 2:");
	mvwscanw(periodwindow,3,1,"%lf",&period);

	//Translating the Variables for the First Investment
	inv1->invest = invest;
	inv1->rate = (rate + 100) / 100;	//Convert the rate from a percent into a decimal for calculation.
	inv1->period = period;
	
	//Collecting Second Investment Info
	mvwscanw(investwindow,2,16,"		%lf",&invest);
	mvwscanw(ratewindow,2,24,"		%lf",&rate);
	mvwscanw(periodwindow,3,24,"		%lf",&period);

	//Translating the Variables for the Second Investment
	inv2->invest = invest;
	inv2->rate = (rate + 100) / 100;	//Convert the rate from a percent into a decimal for calculation.
	inv2->period = period;

	//Clear && NoEcho && Refresh
	clear();
	noecho();
	refresh();

	//Preparing the Table of Values
	WINDOW * calcwindowa = newwin(36,xMax/2,yMax-36,12);
	WINDOW * calcwindowb = newwin(6,12,0,0);
	box(calcwindowa,0,0); box(calcwindowb,0,0);
	keypad(calcwindowb,true);

	//Page System Initialization
	int currentpage = 1;			//The current page. 
	int choice = 0;				//Used to select pages.

	//Getting our windows ready
	wrefresh(calcwindowa); wrefresh(calcwindowb);
	mvwprintw(calcwindowb,1,1,"Use the UP\nand DOWN\narrow keys\nto scroll");

	//Calculation Loop
	while(1){


		int weekshift = 0;								//Shifts the text down the Y axis
		weekinteger = 1 + (33 * (currentpage - 1));					//Defines what 'x' value we'll start at.
		weekfloat = weekinteger;							//Same here.
		wclear(calcwindowa);								//Used to clear out previous page data.
		mvwprintw(calcwindowa,weekinteger,1,"Week 0:		%lf	%lf",inv1->invest,inv2->invest);
		//Above is supposed to be printed consistently at top; but it doesn't work for now.
		box(calcwindowa,0,0);								//Nessicary to get the box back.


		for(int pageinteger = 33 * currentpage; pageinteger != 0 + (33 * (currentpage - 1)); pageinteger--)
		{
			inv1->returns = intrestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			inv2->returns = intrestcalc(inv2->invest,inv2->rate,inv2->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf	%lf",weekinteger,inv1->returns,inv2->returns);
			weekinteger++; weekshift++;;
			weekfloat = weekinteger;
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

	endwin();
	return 0;
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
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * investwindow = newwin(4,xMax-12,yMax-36,6); WINDOW * ratewindow = newwin(4,xMax-12,yMax-32,6);
	WINDOW * periodwindow = newwin(5,xMax-12,yMax-28,6);
	box(investwindow,0,0); box(ratewindow,0,0); box(periodwindow,0,0);

	
	//Window Refreshing
	refresh();
	wrefresh(investwindow); wrefresh(ratewindow); wrefresh(periodwindow);

	//Getting the important information relating to the investment.
	mvwprintw(investwindow,1,1,"Investment:"); mvwscanw(investwindow,2,1,"%lf",&invest);
	mvwprintw(ratewindow,1,1,"Rate Percent:"); mvwscanw(ratewindow,2,1,"%lf",&rate);
	mvwprintw(periodwindow,1,1,"Annual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	mvwprintw(periodwindow,2,1,"Weeks in Period:"); mvwscanw(periodwindow,3,1,"%lf",&period);

	//Calculating the Variables
	inv1->invest = invest;
	inv1->rate = (rate + 100) / 100;	//Convert the rate from a percent into a decimal for calculation.
	inv1->period = period;	
	
	//Clear && NoEcho && Refresh
	clear();
	noecho();
	refresh();

	//Preparing the Table of Values
	WINDOW * calcwindowa = newwin(36,xMax/2,yMax-36,12);
	WINDOW * calcwindowb = newwin(6,12,0,0);
	box(calcwindowa,0,0); box(calcwindowb,0,0);
	keypad(calcwindowb,true);

	//Page System Initialization
	int currentpage = 1;			//The current page. 
	int choice = 0;				//Used to select pages.

	//Getting our windows ready
	wrefresh(calcwindowa); wrefresh(calcwindowb);
	mvwprintw(calcwindowb,1,1,"Use the UP\nand DOWN\narrow keys\nto scroll");

	//Calculation Loop
	while(1){

		int weekshift = 0;								//Shifts the text down the Y axis
		weekinteger = 1 + (33 * (currentpage - 1));					//Defines what 'x' value we'll start at.
		weekfloat = weekinteger;							//Same here.
		wclear(calcwindowa);								//Used to clear out previous page data.
		mvwprintw(calcwindowa,weekinteger,1,"Week 0:		%lf",inv1->invest);	//Printed consistantly at top.
		box(calcwindowa,0,0);								//Nessicary to get the box back.

		for(int pageinteger = 33 * currentpage; pageinteger != 0 + (33 * (currentpage - 1)); pageinteger--)
		{
			inv1->returns = intrestcalc(inv1->invest,inv1->rate,inv1->period,weekfloat);
			mvwprintw(calcwindowa,weekshift+2,1,"Week %d:		%lf",weekinteger,inv1->returns);
			weekinteger++; weekshift++;;
			weekfloat = weekinteger;
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

	getch();
	endwin();
	return 0;
}



//Main
int main(){
	initscr();
	cbreak();

	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * titlewin = newwin(4, xMax-12, yMax-16, 6);
	WINDOW * choicewin = newwin(5, xMax-12, yMax-8, 6);
	box(titlewin, 0, 0); box(choicewin, 0, 0);

	mvwprintw(titlewin, 1, 1, "ACT's Investment-Return Calculator\n Version 2.0");
	mvwprintw(choicewin, 1, 1, "1 or 2 investments?\n");
	refresh(); wrefresh(titlewin); wrefresh(choicewin);
	keypad(choicewin, true);

	int choice;
	int highlight = 1;

	while(1){

		for(int i = 1; i < 3; i++){
			if(i == highlight)
				wattron(choicewin, A_REVERSE);
			mvwprintw(choicewin, i+1, 1, "%d", i);
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
	
	clear();
	endwin();
	if(highlight == 1)
		oneinterest();
	if(highlight == 2)
		twointerest();


	return 0;
}
