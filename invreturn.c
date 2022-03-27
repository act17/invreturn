#include <stdio.h>
#include <stdlib.h>
#include "interesttools.h"

struct investment{	//The investment struct
	double invest;
	double rate;
	double period;
	double returns;
};


//One Investment
int oneinterest(){
	double invest,rate,period,weekfloat;	//Call the important floats,
	int weekinteger,weekcounter;		//Call the integers for counting weeks,
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1;		//Call a struct for the investment as a pointer. (Thanks to Xen on the Ubuntu Discord.)


	//Getting the important information relating to the investment.
	printf("\n		Investment");
	printf("\nInvestment:		");	scanf(" %lf",&invest);
	printf("\nRate Percent:		");	scanf(" %lf",&rate);
	printf("\nAnnual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	printf("\nWeeks in Period:	");	scanf(" %lf",&period);	
	rate = rate + 100;		//Convert the rate inputted as a rate + 100%.
	printf("\nInvestment: %lf		Rate: %lf Percent	Period: %lf Weeks",invest,rate,period);

	inv1->invest = invest;
	inv1->rate = rate / 100;	//Convert the rate from a percent into a decimal for calculation.
	inv1->period = period;
	printf("\nWeeks of Calculation:	");	scanf(" %d",&weekcounter);

	for(inv1->returns = 0; weekcounter != 0; weekcounter--){
		inv1->returns = interestcalc(inv1->invest, inv1->rate, inv1->period, weekfloat);
		printf("\nWeek %d:	%lf",weekinteger,inv1->returns);
		weekinteger++;
		weekfloat = weekinteger;
	}
	printf("\n");
	return 0;
}


//Two Investments
int twointerest(){
	double invest,rate,period,weekfloat;
	int weekinteger,weekcounter;
	weekinteger = 1;
	weekfloat = weekinteger;
	struct investment *inv1 = malloc(sizeof(*inv1));
	struct investment *inv2 = malloc(sizeof(*inv2));


	//Entering of information on the first investment.
	printf("\n		First Investment");
	printf("\nInvestment:		");	scanf(" %lf",&invest);
	printf("\nRate Percent:		");	scanf(" %lf",&rate);
	printf("\nAnnual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	printf("\nWeeks in Period:	");	scanf(" %lf",&period);	
	rate = rate + 100;
	printf("\nInvestment: %lf		Rate: %lf Percent	Period: %lf Weeks",invest,rate,period);
	
	inv1->invest = invest;
	inv1->rate = rate / 100;
	inv1->period = period;


	//Entering of information on the second investment.
	printf("\n\n		Second Investment");
	printf("\nInvestment:		");	scanf(" %lf",&invest);
	printf("\nRate Percent:		");	scanf(" %lf",&rate);
	printf("\nAnnual = 52, Semiannual = 26, Quarterly = 13, Monthly = 4.3");
	printf("\nWeeks in Period:	");	scanf(" %lf",&period);	
	rate = rate + 100;
	printf("\nInvestment: %lf		Rate: %lf Percent	Period: %lf Weeks",invest,rate,period);

	inv2->invest = invest;
	inv2->rate = rate / 100;
	inv2->period = period;


	//Calculation of the returns on investment 1 and investment 2.
	weekcounter = 0;
	printf("\nWeeks of Calculation:	");	scanf(" %d",&weekcounter);
	printf("\n		Investment 1		Investment 2");
	printf("\nWeek 0:	%lf		%lf",inv1->invest,inv2->invest);
	for( ; weekcounter != 0; weekcounter--){
		inv1->returns = interestcalc(inv1->invest, inv1->rate, inv1->period, weekfloat);
		inv2->returns = interestcalc(inv2->invest, inv2->rate, inv2->period, weekfloat);
		printf("\nWeek %d:	%lf	%lf",weekinteger,inv1->returns,inv2->returns);
		weekinteger++;
		weekfloat = weekinteger;
	}


	//Comparing the two investments to see which is more profitable.
	printf("\n\n		Comparative Statistics");
	double gains;
	weekinteger--;
	if(inv1->returns > inv2->returns)
	{
		gains = inv1->returns / inv2->returns;
		gains = gains * 100.0;
		printf("\nInvestment 1 is %lf percent more profitable than Investment 2 by Week %d.",gains,weekinteger);
	}
	if(inv2->returns > inv1->returns)
	{
		gains = inv2->returns / inv1->returns;
		gains = gains * 100.0;
		printf("\nInvestment 2 is %lf percent more profitable than Investment 1 by Week %d.",gains,weekinteger);
	}
	else if(inv1->returns == inv2->returns)
	{
		printf("\nThe two investments are exactly the same.");
	}
	printf("\n");
	return 0;
}



//Main
int main(){
	int mode = 0;
	int looper = 0;

	printf("\n		Investment Calculator");
	printf("\n1 or 2 Investments? ");
	do{
		scanf(" %d",&mode);
		if(mode == 1){ oneinterest(); looper = 1; }
		if(mode == 2){ twointerest(); looper = 1; }
		if(mode != 1 || mode != 2){ printf("\n"); }
	}while(looper < 1);
	return 0;
}
