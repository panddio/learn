#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_samechar(char *str)
{
	char ch[127] = {0};
	int i = 0;

	if(str == NULL) return 0;

	while(str[i] != 0){
		if(ch[str[i]] == 0){
			ch[str[i]] = str[i];
		}
		else return 1;
		i++;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	char str[64] = "";
	int len = 0;

	printf("输入字符串：");
	// 刷新标准输出，因为在printf函数的缓冲没满，并且打印的
	// 字符串后面没有 "\n"，调用这个函数屏幕马上可以看到”输入字符串：“
	fflush(stdout);

	fgets(str, sizeof(str), stdin); // 从标准输入获取输入字符串
	len = strlen(str); // 求出长度
	str[len - 1] = 0;  // 去掉字符串后的换行符

	int flag = check_samechar(str); // 处理

	if(flag == 1)
		printf("##:%s\n", str);

	return 0;
}
