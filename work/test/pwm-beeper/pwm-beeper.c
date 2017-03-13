/*************************************************************************
	> File Name: pwm-beeper.c
	>    Author: Qiuwei Wang
	>      Mail: qiuwei.wang@ingenic.com
	>  Datatime: Wed 09 Nov 2016 03:35:40 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define DEFAULT_DEV  "event0"


int main(int argc, char *argv[])
{
    int fd;
    int i;
    char dev[32] = "/dev/input/";
    struct input_event event;

    if(argc > 1)
        strcat(dev, argv[1]);
    else
        strcat(dev, DEFAULT_DEV);


    fd = open(dev, O_RDWR);
    if(fd < 0) {
        printf("Open %s failed\n", dev);
        return 1;
    }

    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 0;

    for(i = 1; i < 10; i++) {
        event.value = i * 100;
        printf("event0.value = %d\n", event.value);
        write(fd, &event,sizeof(event));
        //sleep(1);
    }

    event.value = 1004000;
    write(fd, &event, sizeof(event));

    while(1)
        sleep(1);
    close(fd);
    return 0;
}
