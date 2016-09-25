#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
char *get_samechar(char *str)
{
	if(str == NULL)
		return NULL;

	char *p = NULL, *ret = NULL;
	int i = 0, j = 1;
	int len = strlen(str) + 1;// 测出传入字符串长度

	p = (char *)malloc(len);  // 动态分配内存空间，len个字节长度
	bzero(p, len); // 清零

	while(j<len){
		//printf("j = %d\n", j);
		if(str[i] == str[j]){ // 出现连续字符有相同
			p[i] += 2; // 在出现连续相同字符 对应 在字符串中的位置 记录出现的次数，
			j++;
			while(j < len && str[i] == str[j]){ // 判断后面还是不是相同字符
				p[i] += 1; // 记录加1
				j++; // 指向下一个
			}
			i = j;
			j++;
		}
		else{
			i++;
			j++;
		}
	}

	for(i=0,j=1; j<len; j++){
		if(p[i] < p[j])
			i = j;
	}

	if(p[i] != 0) ret = str + i;
	else ret = NULL;
	free(p); // 释放动态分配的内存空间，malloc函数分配的空间在不要时要释放掉

	return ret;
}
#else

char *get_samechar(char *str)
{
	if(str == NULL)
		return NULL;
	int i = 0, j = 1, len = strlen(str);
	int pos = 0, len_new = 0, len_old = 0;

	while(j < len){
		if(str[i] == str[j]){
			len_new += 2;
			j++;
			while(str[j] != 0 && str[i] == str[j]){
				len_new++;
				j++;
			}

			if(len_new > len_old)
				len_old = len_new;

			pos = i;
			i = j + 1;
			j++;
		}
		else{
			i++;
			j++;
		}
	}

	if(len_old != 0)
		return str + pos;
	else
		return NULL;
}
#endif

int main(int argc, char argv[])
{

	char str[64] = "";
	int len = 0;

	printf("输入字符串：");
	// 刷新标准输出，因为在printf函数的缓冲没满，并且打印的
	//字符串后面没有 "\n"，调用这个函数屏幕马上可以看到”输入字符串：“
	fflush(stdout);

	fgets(str, sizeof(str), stdin); // 从标准输入获取输入字符串
	len = strlen(str); // 求出长度
	str[len - 1] = 0;  // 去掉字符串后的换行符

	char *p = get_samechar(str); // 处理

	if(p != NULL){

		printf("##:%s\n", p);
	}

	return 0;
}
