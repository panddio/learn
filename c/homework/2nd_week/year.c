/* ************************************************************************
 *       Filename:  year.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月16日 星期四 09時17分41秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int main(int argc, char *argv[])
{
	char i = 0;
	int countday = 0;
	int year = 0, month = 0, day = 0;
	
	printf("-----------------------------------------\n");

	again:
	printf("Please input the year, month, day.\n");
	scanf("%d %d %d",&year,&month,&day);

	if(year<0 || month<0 ||month >12 || day<0)
	{
		printf("error! input again!\n");
		goto again;
	}
	else
	{
		switch(month)
		{
			case  1:
			case  3:
			case  5:
			case  7:
			case  8:
			case 10:
			case 12:
					checkday1:
					if(day>31)
					{
						printf("Please input a day between 1 to 31!\n");
						scanf("%d",&day);
						goto checkday1;
					}
					break;

			case  4:
			case  6:
			case  9:
			case 11:
					checkday2:
					if(day>30)
					{
						printf("Please input a day between 1 to 30\n");
						scanf("%d",&day);
						goto checkday2;
					}
					break;
		}
	}



	if((year%4 == 0 && year%100 != 0) || (year%400 == 0))
	{
		printf("%d is a leap year!\n",year);
		months[1] = 29;
		if((month == 2) && (day > 29))
		{
			printf("Please input a day between 1 to 29!\n");
			scanf("%d",&day);
		}
	}
	else
	{

		printf("%d is not a leap year!\n",year);
		months[1] = 28;
		if((month == 2) && (day > 28)) 
		{		
			printf("Please input a day between 1 to 28!\n");
			scanf("%d",&day);
		}
	}
	
	for(i=0;i<month-1;i++)
	{
		countday += months[i];
	}

	countday += day;
	
	printf("The day you input is the %d'th day of %d.\n",countday,year);
	printf("-------------- %d.%d.%d ----------------\n",year,month,day);
	return 0;
}


