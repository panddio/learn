/*************************************************************************
	> File Name: gpioset.c
	> Author:
	> Mail:
	> Created Time: Tue 24 May 2016 04:36:11 PM CST
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

// Functions declaration
static void print_help(void);
static int gpio_export(int pin);
static int gpio_unexport(int pin);
static int gpio_direction(int pin, int dir);
static int gpio_read(int pin);

static void print_help(void)
{
    printf("Usage: gpioset gpionum I/O/H/L/R\n");
    printf("Usage:\n");
    printf("    I -> set gpio input\n");
    printf("    O -> set gpio output\n");
    printf("    H -> set gpio output 1\n");
    printf("    L -> set gpio output 0\n");
    printf("    R -> read gpio value\n");
    printf("   eg: gpioset 52 I\n");
}

static int gpio_export(int gpionum)
{
    char buffer[64];
    int len, fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd < 0) {
        printf("Failed to open export for writing!\n");
        return -1;
    }

    len = snprintf(buffer, sizeof(buffer),"%d", gpionum);
    if(write(fd, buffer, len) < 0) {
        printf("Failed to export gpio%d!\n", gpionum);
        return -1;
    }

    close(fd);
    return 0;
}

static int gpio_unexport(int gpionum)
{
    char buffer[64];
    int len, fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd < 0) {
        printf("Failed to open upexport for writing!\n");
        return -1;
    }

    len = snprintf(buffer, sizeof(buffer),"%d", gpionum);
    if(write(fd, buffer, len) < 0) {
        printf("Failed to upexport gpio%d!\n", gpionum);
        return -1;
    }

    close(fd);
    return 0;
}

//dir: 0 -> in, 1-> out
static int gpio_direction(int gpionum, int dir)
{
    static const char dir_str[] = "in\0out";
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpionum);
    fd = open(path, O_WRONLY);
    if(fd < 0) {
        printf("Failed to open gpio direction for writing!\n");
        return -1;
    }

    if(write(fd, &dir_str[dir == 0?0:3], dir == 0?2:3) < 0) {
        printf("Failed to set gpio%d direction!\n", gpionum);
        return -1;
    }

    close(fd);
    return 0;
}

//value: 0 -> LOW, 1 -> HIGH
static int gpio_write(int gpionum, int value)
{
    char path[64];
    char value_str[3] = "01";
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpionum);
    fd = open(path, O_WRONLY);
    if(fd < 0) {
        printf("Failed to open gpio value for reading!\n");
        return -1;
    }

    if(write(fd, &value_str[value == 0?0:1], 1) < 0) {
        printf("Failed to write gpio%d value!\n", gpionum);
        return -1;
    }

    close(fd);
    return 0;
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
    if(argc != 3) {
        print_help();
        return -1;
    }

    int gpionum = atoi(argv[1]);
    if(gpionum < 0 || gpionum > 101) { // For Ingenic x1000 soc
        printf("### gpionum: %d is invalid ###\n", gpionum);
        return -1;
    }

    int ret = gpio_export(gpionum);
    if(ret < 0)
        return -1;

    char opt;
    memcpy(&opt, argv[2], 1);

    switch(opt) {
    case 'I': // Set gpio direction as input
        gpio_direction(gpionum, GPIO_SET_INPUT);
        break;
    case 'O': // Set gpio dirextion as output
        gpio_direction(gpionum, GPIO_SET_OUTPUT);
        break;
    case 'H': // Set gpio output 1
        ret = gpio_direction(gpionum, GPIO_SET_OUTPUT);
        if(ret != -1)
            gpio_write(gpionum, GPIO_SET_HIGH);
        break;
    case 'L': // Set gpio output 0
        ret = gpio_direction(gpionum, GPIO_SET_OUTPUT);
        if(ret != -1)
            gpio_write(gpionum, GPIO_SET_LOW);
        break;
    case 'R': // Read gpio value
        ret = gpio_read(gpionum);
        if(ret != -1)
            printf("### read gpio%d ret = %d ###\n", gpionum, ret);
        break;
    default:
        print_help(); // Show help when entry a wrong argument
    }

    printf("### Successful opetation! ###\n");
    gpio_unexport(gpionum);
    return 0;
}
