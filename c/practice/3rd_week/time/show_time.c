/* ************************************************************************
 *       Filename:  show_time.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月28日 星期二 05時37分22秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <time.h>
#include <sys/time.h>


void show_time(void)
{
	time_t rawtime;
	struct tm *timeinfo;
	int i = 0;
	//time(&rawtime);     //获取系统时间
	//timeinfo = localtime(&rawtime);//转为本地时间
	

	while(1)
	{
#if 1
		system("clear");
		
		time(&rawtime);     //获取系统时间
		timeinfo = localtime(&rawtime);//转为本地时间
		//asctime(timeinfo);  //转为便准的ASCII时间格式
		printf("%4d-%02d-%02d  %02d:%02d:%02d\n",
			timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,
			timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
						
		sleep(1);	
#endif


#if 0	
		usleep(990900); //1ms	
		i++;
		
		if(1)
		{
			//i = 0;
			
			timeinfo->tm_sec++;
		
			if(timeinfo->tm_sec == 60)
			{
				timeinfo->tm_sec = 0;
				timeinfo->tm_min++;
			
				if(timeinfo->tm_min == 60)
				{
					timeinfo->tm_min = 0;
					timeinfo->tm_hour++;
				
					if(timeinfo->tm_hour == 24)
					{
						timeinfo->tm_hour = 0;
					}
				}
			}
			
			system("clear");
		
			printf("%4d-%02d-%02d  %02d:%02d:%02d\n",
					timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,
					timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
		}
#endif		
	}
	
}



