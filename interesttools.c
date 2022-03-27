#include <stdio.h>
#include <math.h>

double interestcalc(double investment, double rate, double period, double week)
{
	double returns;
	week = week/period;
	returns = pow(rate,week);
	returns = returns*investment;
	return returns;
}
