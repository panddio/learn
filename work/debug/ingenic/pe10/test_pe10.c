#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define PE10_IOC_MAGIC     'p'
#define PE10_SET_ON_TIMER  _IO(PE10_IOC_MAGIC, 1) 
#define PE10_SET_OFF_TIMER _IO(PE10_IOC_MAGIC, 2)

int main(int argc, char *argv[])
{
	char cmd[64] = {0};
	char *pcmd[5] = {NULL};
	int fd = 0, arg = 0, i = 0;
	
	fd = open("/dev/pe10_gpio", O_RDWR);
	if(fd <0){
		printf("open '/dev/pe10_gpio' failed\n");
		return -1;
	}
	
	while(1) {
		bzero(cmd, sizeof(cmd));
		
		printf("\033[31mCMD: \033[0m");
		fflush(stdout);
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = 0;
		
		if(strlen(cmd) == 0)
			continue;
		i = 0;
		pcmd[i++] = strtok(cmd, " ");
		if(pcmd[0] != NULL) {
			pcmd[i++] = strtok(NULL, " ");
		}
		
		if(strcmp(pcmd[0], "on") == 0) {
			if(pcmd[1] != NULL) {
				arg = atoi(pcmd[1]);
				printf("set on time as %d\n", arg);
				ioctl(fd, PE10_SET_ON_TIMER, arg);	
			}
			else
				printf("set on time : on <value>\n");
		}
		else if(strcmp(pcmd[0], "off") == 0) {
			if(pcmd[1] != NULL) {
				arg = atoi(pcmd[1]);
				printf("set off time as %d\n", arg);
				ioctl(fd, PE10_SET_OFF_TIMER, arg);
			}
			else
				printf("set off time: off <value>\n");
		}
		else if(strcmp(pcmd[0], "help") == 0) {
			printf("\033[34mset on time : on <value>\033[0m\n");
			printf("\033[34mset off time: off <value>\033[0m\n");
			printf("\033[34msetting exit: q\n");		
		}
		else if(strcmp(pcmd[0], "q") == 0) {
			break;
		}
		else {
			printf("wrong cmd, input 'help' to get help.\n");
		}
	}
	
	close(fd);
	return 0;
}

