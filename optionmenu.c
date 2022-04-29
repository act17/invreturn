#include <ncurses.h>
#include <stdlib.h>

int optionmenu(int color)
{
	//Initializing
	initscr();
	cbreak();
	noecho();
	start_color;

	//Color-Pairs
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_CYAN,COLOR_CYAN);
	init_pair(3,COLOR_GREEN,COLOR_GREEN);
	init_pair(4,COLOR_MAGENTA,COLOR_MAGENTA);

	//Windows
	WINDOW * titlewin = newwin(3,86,0,0);
	WINDOW * selectwin = newwin(6,86,3,0);

	wbkgd(stdscr,COLOR_PAIR(color));
	wattron(titlewin,COLOR_PAIR(1));	wbkgd(titlewin,COLOR_PAIR(1));	
	wattron(selectwin,COLOR_PAIR(1));	wbkgd(selectwin,COLOR_PAIR(1));
	
	box(titlewin,0,0);	box(selectwin,0,0);

	keypad(selectwin,true);

	//Printing Info
	mvwprintw(titlewin,1,1,"Options Menu");
	mvwprintw(selectwin,1,1,"Color:");

	//Refresh
	refresh();	wrefresh(titlewin);	wrefresh(selectwin);
	
	//Menu
	int choice;
	int highlight = 1;
	char colors[3][64] = {"Cyan", "Green", "Magenta"};

	while(1){

		for(int i = 1; i < 4; i++)
		{
			if(i == highlight)
				wattron(selectwin,A_REVERSE);
			mvwprintw(selectwin,i+1,10,"%s",colors[i - 1]);
			wattroff(selectwin,A_REVERSE);
		}
		choice = wgetch(selectwin);
		switch(choice)
		{
			case KEY_UP:
				if(highlight == 1)
					break;
				highlight--;
				break;
			
			case KEY_DOWN:
				if(highlight == 3)
					break;
				highlight++;
				break;

			default:
				break;
		}
		
		if(choice == 10)
			break;
	}

	highlight++;
	return highlight;
}
