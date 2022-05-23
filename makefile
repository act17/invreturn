invreturn: invreturn.c interesttools.c oneinterest.c twointerest.c ratefinder.c optionmenu.c
	gcc -o $@ $^ -w -Wall -lm -lncurses -lpthread

clean:
	rm invreturn
