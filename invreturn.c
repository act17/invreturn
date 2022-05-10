#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "interest.h"
#include "optionmenu.h"

void* timedisplay(void * arg){
	initscr();
	noecho();

	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	attron(COLOR_PAIR(1));
	
	time_t s;
	struct tm* currtime;
	
	while(1){
		s = time(NULL);
		currtime = localtime(&s);
		mvwprintw(stdscr,16,2,"The time is: %02d:%02d:%02d",currtime->tm_hour,currtime->tm_min,currtime->tm_sec);
		refresh();
		sleep(1);
	}

	return NULL;
}

int main(){
	
	//Options
	int color = 2;	//Background color. By default, it's set to cyan.
	
while(1){

	initscr();
	cbreak();
	noecho();
	start_color();
	int optionflag = 0;

	//Error Check
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);		//Program needs at least 36 y-axis units and 86 x-axis units.
	if(yMax < 36 || xMax < 86){		//If window cannot meet those requirements it stops and prints an error code.
		endwin();
		printf("\nError!\nError Code:		01\nWindow Dimensions too small!");
		printf("\nyMax = %d			xMax = %d",yMax,xMax);
		printf("\nyMax must be at least 36.	xMax must be at least 86.");
		return 1;
	}

	//Color Pairs (See 'optionmenu')
	init_pair(1,COLOR_BLACK,COLOR_WHITE);			//Color-pair 1 (Windows) is a nice combo of Black and White (Grey)
	init_pair(2,COLOR_CYAN,COLOR_CYAN);			//Color-pair 2 (Background) is Cyan (Default)
	init_pair(3,COLOR_GREEN,COLOR_GREEN);			//Color-pair 3 (Background) is Green
	init_pair(4,COLOR_MAGENTA,COLOR_MAGENTA);		//Color-pair 4 (Background) is Magenta


	//Initializing the screen.
	WINDOW * titlewin = newwin(4,86,0,0);
	WINDOW * choicewin = newwin(5,86,4,0);
	WINDOW * infowin = newwin(5,86,9,0);
	WINDOW * extrawin = newwin(5,86,14,0);
	
	wbkgd(stdscr, COLOR_PAIR(color));
	wattron(titlewin,COLOR_PAIR(1));	wbkgd(titlewin,COLOR_PAIR(1));
	wattron(choicewin,COLOR_PAIR(1));	wbkgd(choicewin,COLOR_PAIR(1));
	wattron(infowin,COLOR_PAIR(1));		wbkgd(infowin,COLOR_PAIR(1));
	wattron(extrawin,COLOR_PAIR(1));	wbkgd(extrawin,COLOR_PAIR(1));

	box(titlewin,0,0); box(choicewin,0,0); box(infowin,0,0); box(extrawin,0,0);
	
	mvwprintw(titlewin,1,2, "ACT's Investment-Return Calculator");
	mvwprintw(choicewin,1,2,"1 or 2 investments?");
	mvwprintw(infowin,1,2,"Copyright 2022 ACT");
	mvwprintw(infowin,2,2,"Licensed under the GNU GPL 3.0");
	mvwprintw(infowin,3,2,"https://github.com/act17/invreturn");
	mvwprintw(extrawin,1,2,"Version 2.6 - May 9th, 2022");
	mvwprintw(extrawin,3,2,"Press 'x' to exit, press 'o' for options.");

	refresh(); wrefresh(titlewin); wrefresh(choicewin); wrefresh(infowin); wrefresh(extrawin);
	keypad(choicewin, true);

	//pThread
	pthread_t timethread;
	pthread_create(&timethread, NULL, timedisplay, NULL);
	

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
				return 0;
			default:
				break;
		}

		if(choice == 'x'){
			clear();
			endwin();
			pthread_cancel(timethread);
			return 0;
		}

		if(choice == 'o'){
			optionflag++;
			clear();
			endwin();
			pthread_cancel(timethread);
			color = optionmenu(color);
			break;
		}
		if(choice == 10)
			break;
	}
	

	//Opening the functions to calculate one or two interests
	clear();
	endwin();
	pthread_cancel(timethread);
	
	if(optionflag == 0)		//Execute (Which performs the interest stuff) if options haven't been opened this loop.
	{
	if(highlight == 1)
		oneinterest(color);
	if(highlight == 2)
		twointerest(color);
	}

	}
	return 0;
}
