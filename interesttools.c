#include <stdio.h>
#include <math.h>

double interestcalc(double investment, double rate, double period, double week)
{
	return investment * pow(rate, week / period);	//Thanks to 'rene' on the Linux Mint Forums for providing this simplified
							//function.
}
