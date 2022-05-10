#include <stdio.h>
#include <math.h>

double interestcalc(double investment, double rate, double period, double week)
{
	return investment * pow(rate, week / period);	//Thanks to 'rene' on the Linux Mint Forums for providing this simplified
							//function.
}

double interestfind(double benchmark, double investment, double rate, double period)
{
	return ((log(benchmark/investment)/log(rate)) * period);
}

int weekfind(double week){
	int weekcount = 1;
	
	if(week < 34)
		return 1;

	while(1){
		int weekcheck = week - (33 * weekcount);
		if(weekcheck < 34)
			break;
		else
			weekcount++;
	}
	return weekcount + 1;
}
