/* ************************************************************************
 *       Filename:  petrol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月20日 星期一 09時36分43秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>

#define	APRICE (1.50f)
#define BPRICE (1.35f)
#define CPRICE (1.18f)

typedef enum 
{
	agas = 'a',
	bgas = 'b',
	cgas = 'c',
}GAS;

typedef enum
{
	ato = 'f',
	own = 'm',
	ass = 'e',
}SERVER;


float get_gasoline(char service, char gasoline, float kg)
{
	float gas_price;
	float discount;

	switch(service)
	{
		case ato: discount = 0.00f; break;
		case own: discount = 0.05f; break;
		case ass: discount = 0.10f; break;
	}

	switch(gasoline)
	{
		case agas: 
				{
					gas_price = (APRICE * (1-discount)) * kg;
					break;
				}
		case bgas: 
				{
					gas_price = (BPRICE * (1-discount)) * kg;
					break;
				}
		case cgas: 
				{
					gas_price = (CPRICE * (1-discount)) * kg;
					break;
				}	
	}

	return gas_price;
}
int main(int argc, char *argv[])
{
	float price;
	float kg;
	char service,gasoline,temp;

	printf("请选择服务类型，输入：f | m | e\n");
	printf("f--自动服务，无优惠！\n");
	printf("m--自助服务，优惠%5！\n");
	printf("e--协助服务，优惠%10！\n");
	scanf("%c%c",&service,&temp);
//	service = getchar();

	printf("请选择汽油类型，输入：a | b | c\n");
	scanf("%c",&gasoline);
//	gasoline = getchar();
	printf("请输入本次加油量，单位：KG\n");
	scanf("%f",&kg);

	price = get_gasoline(service,gasoline,kg);
	printf("本次加油总价为 %.2f 元\n",price);

	return 0;
}


