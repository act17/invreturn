#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include "interesttools.h"

void ratefinder(int color){
	//Variables
	double benchmark;
	double timeframe = 0;
	double investment;
	//Structs
	struct data{
		double period;
		double rate;
		double weeks;
	};
	struct data *ann = malloc(sizeof(*ann));	//Annual
	struct data *sem = malloc(sizeof(*sem));	//Semi-Annual
	struct data *qrt = malloc(sizeof(*qrt));	//Quarter-Annual
	struct data *mth = malloc(sizeof(*mth));	//Monthly
	struct data *cus = malloc(sizeof(*cus));	//Custom
	ann->period = 52;	sem->period = 26;
	qrt->period = 13;	mth->period = 4.3;
	cus->period = 0;
	//NCurses Init 1
	echo();
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_CYAN,COLOR_CYAN);
	init_pair(3,COLOR_GREEN,COLOR_GREEN);
	init_pair(4,COLOR_MAGENTA,COLOR_MAGENTA);
	wbkgd(stdscr,COLOR_PAIR(color));
	WINDOW * entrywindow = newwin(10,86,0,0);
	wbkgd(entrywindow,COLOR_PAIR(1));
	wattron(entrywindow,COLOR_PAIR(1));
	box(entrywindow,0,0);
	mvwprintw(entrywindow,1,1,"Enter the return:");
	mvwprintw(entrywindow,2,1,"$");
	mvwprintw(entrywindow,3,1,"Enter the investment:");
	mvwprintw(entrywindow,4,1,"$");
	mvwprintw(entrywindow,5,1,"Enter a custom period (Optional):");
	mvwprintw(entrywindow,7,1,"Enter the week the return is needed (Optional):");
	refresh();
	wrefresh(entrywindow);
	//I/O
	while(1){
		mvwscanw(entrywindow,2,2,"%lf",&benchmark);
		if(benchmark != 0)
			break;
		mvwprintw(entrywindow,2,10,"Error: Cannot be 0!");
	}
	while(1){
		mvwscanw(entrywindow,4,2,"%lf",&investment);
		if(benchmark != 0)
			break;
		mvwprintw(entrywindow,2,10,"Error: Cannot be 0!");
	}
	mvwprintw(entrywindow,2,10,"			");
	mvwscanw(entrywindow,6,1,"%lf",&cus->period);
	mvwscanw(entrywindow,8,1,"%lf",&timeframe);
	//Free Memory and Clear Screen
	wclear(entrywindow);
	delwin(entrywindow);
	//NCurses Init 2
	WINDOW * outputwindow = newwin(15,86,0,0);
	wbkgd(outputwindow,COLOR_PAIR(1));
	wattron(outputwindow,COLOR_PAIR(1));
	box(outputwindow,0,0);
	mvwprintw(outputwindow,1,1,"You will see $%lf made by...",benchmark);
	mvwprintw(outputwindow,2,1,"Prd:%lf	%lf	%lf	%lf	",ann->period,sem->period,qrt->period,mth->period);
		if(cus->period != 0)
			mvwprintw(outputwindow,2,63,"%lf",cus->period);
	//Calculations
	if(timeframe == 0){	//If our timeframe given is zero, then we calculate using a timeframe of 1 period.
		//These 5 functions calculate the rate of the investment.
		ann->rate = ratefind(benchmark,investment,ann->period,ann->period);
		sem->rate = ratefind(benchmark,investment,sem->period,sem->period);
		qrt->rate = ratefind(benchmark,investment,qrt->period,qrt->period);
		mth->rate = ratefind(benchmark,investment,mth->period,mth->period);
		if(cus->period != 0)
			cus->rate = ratefind(benchmark,investment,cus->period,cus->period);
		//These 5 functions calculate the weeks needed to reach the benchmark.
		ann->weeks = interestfind(benchmark,investment,ann->rate,ann->period);
		sem->weeks = interestfind(benchmark,investment,sem->rate,sem->period);
		qrt->weeks = interestfind(benchmark,investment,qrt->rate,qrt->period);
		mth->weeks = interestfind(benchmark,investment,mth->rate,mth->period);
		if(cus->period != 0)
			cus->weeks = interestfind(benchmark,investment,cus->rate,cus->period);
	}
	if(timeframe != 0){	//Otherwise, we use the user-inputted timeframe.
		ann->rate = ratefind(benchmark,investment,timeframe,ann->period);
		sem->rate = ratefind(benchmark,investment,timeframe,sem->period);
		qrt->rate = ratefind(benchmark,investment,timeframe,qrt->period);
		mth->rate = ratefind(benchmark,investment,timeframe,mth->period);
		if(cus->period != 0)
			cus->rate = ratefind(benchmark,investment,timeframe,cus->period);
	}
	//Ncurses Init 3
	wattron(outputwindow,A_REVERSE);
	mvwprintw(outputwindow,3,1,"Rt%:%lf	%lf	%lf	%lf",ann->rate,sem->rate,qrt->rate,mth->rate);
	if(cus->period != 0)
		mvwprintw(outputwindow,3,63,"%lf",cus->rate);
	wattroff(outputwindow,A_REVERSE);
	if(timeframe != 0)
		mvwprintw(outputwindow,5,1,"By week %lf",timeframe);
	refresh(); wrefresh(outputwindow);
	getch();
	free(ann); free(sem); free(qrt); free(mth); free(cus);
	return 0;
	//Note: This really needs to get made more effecient. Lots of if-statements that can be removed.
	//Too lazy to do it for now.
}
