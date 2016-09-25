/* ************************************************************************
 *       Filename:  mate_bracket.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年11月17日 20时31分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  mate_bracket(char *str)
{
	char *p = NULL;
	int i = 0, j = 0, len = strlen(str);

	p = (char *)malloc(len + 1);
	memset(p, 0, len+1);

	for(i=0;i<len;i++)
	{
		if(str[i] == '(' || str[i] == '[' 
		|| str[i] == '{' || str[i] == '<')
		{
			p[j] = str[i];
			j++;
			continue;
		}

		switch(str[i])
		{
			case ')':
				j--;
				if(j < 0 || p[j] != '(')
					return 0;
				break;	

			case ']':
				j--;
				if(j < 0 || p[j] != '[')
					return 0;
				break;

			case '}':

				j--;
				if(j < 0 || p[j] != '{')
					return 0;
				break;
			case '>':
				j--;
				if(j < 0 || p[j] != '<')
					return 0;
				break;
		}
	}

	free(p);
	if(j != 0)
		return 0;
	else
		return 1;

}


int main(int argc, char *argv[])
{
	char exp[128] = {0};
	int ret, len;

	fgets(exp, sizeof(exp),stdin);
	len = strlen(exp);
	exp[len - 1] = 0;


	ret = mate_bracket(exp);

	printf("ret = %d\n",ret);

	return 0;
}


