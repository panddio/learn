#include <stdio.h>
#include <string.h>
#include "mystring.h"

void main()
{
	char a[]="jkdjgse";
	char b[20]="hjakh";
	char c[]="12345";
	int num = 0;

	mystrinv(a);
	printf("a=%s\n",a);
	printf("%d\n",mystrcmp(a,b));

	num = strchange(c);
	printf("num=%d\n",num);

	mystrcpy(b,a);
	printf("b=%s\n",b);
}
