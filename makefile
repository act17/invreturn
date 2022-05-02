invreturn: invreturn.c interesttools.c oneinterest.c twointerest.c optionmenu.c
	gcc -o $@ $^ -lm -lncurses -lpthread

clean:
	rm invreturn
