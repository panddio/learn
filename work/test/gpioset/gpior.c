/*************************************************************************
	> File Name: gpio.c
	> Author:
	> Mail:
	> Created Time: Wed 25 May 2016 10:50:56 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*#define DEBUG*/
#define GPIO_SET_OUTPUT  1
#define GPIO_SET_INPUT   0
#define GPIO_SET_LOW     0
#define GPIO_SET_HIGH    1

static void print_help(void)
{
    printf("Usage: gpior gpionum \n");
    printf("Usage:\n");
    printf("   eg: gpior 52\n");
}

static int gpio_read(int gpionum)
{
    char path[64];
    char value_str[3] = {0};
    int fd, i;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpionum);
    printf("path: %s\n",path);
    fd = open(path, O_RDONLY);
    if(fd < 0) {
        printf("Failed to open gpio value for reading!\n");
        return -1;
    }

    for(i = 0; i < 2; i++) {
        if(read(fd, value_str, sizeof(value_str)) < 0) {
          printf("Failed to read gpio%d value!\n", gpionum);
          return -1;
        }
    }
#ifdef DEBUG
    printf("### read value = %s\n", value_str);
    for(i = 0; i < 3; i++) {
        printf("value_str[%d] = %d\t",i, value_str[i]);
    }
    printf("\n");
#endif
    close(fd);
    return atoi(value_str);
}

int main(int argc, char *argv[])
{
    // Test for correct number of arguments
    if(argc != 2) {
        print_help();
        return -1;
    }

    int gpionum = atoi(argv[1]);
    if(gpionum < 0 || gpionum > 101) { // For Ingenic x1000 soc
        printf("### gpionum: %d is invalid ###\n", gpionum);
        return -1;
    }
     int ret = gpio_read(gpionum);
     if(ret != -1)
         printf("### read gpio%d ret = %d ###\n", gpionum, ret);
     return 0;
}
