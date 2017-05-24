#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#if 1// test keys_drv
int main(void)
{
	char key = 0;
	int fp;

	fp = open("/dev/keys_drv", O_RDWR);
	if(fp <0)
	{
		printf("open failed\n");
		return -1;
	}
	
	while(1)
	{
		read(fp, &key, sizeof(key)); //´ø×èÈû¶ÁÈ¡
		
		if(key <12 && key >1)
			printf("the key = %d\n",key);
	}
	close(fp);
	return 0;
}
#endif