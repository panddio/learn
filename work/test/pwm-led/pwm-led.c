/*************************************************************************
	>File Name: pwm-led.c
	>   Author: Qiuwei Wang
	>     Mail: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Thu 03 Nov 2016 07:45:42 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Macro
 */
#define JZ_GENERIC_PWM          0
#define DEFAULT_MAX_BRIGHTNESS  255
#define DEFAULT_DELAY_US        40000
#define DEFAULT_LED            "led_state"

/*
 * Variables
 */
const float duty[] = {
    0.00, 0.01, 0.02, 0.03,
    0.04, 0.05, 0.06, 0.07,
    0.09, 0.10, 0.11, 0.13,
    0.15, 0.17, 0.19, 0.21,
    0.23, 0.25, 0.27, 0.29,
    0.31, 0.33, 0.35, 0.38,
    0.41, 0.44, 0.47, 0.50,
    0.53, 0.56, 0.59, 0.62,
    0.66, 0.70, 0.74, 0.79,
    0.84, 0.89, 0.94, 1.00,
};

/*
 * Function
 */
void print_usage()
{
    printf("Usage:\n \
        pwm-led [OPTIONS]\n \
            a pwm-leds test demo\n\n \
        OPTIONS:\n \
            -l   ----> select led name\n \
            -m   ----> select pwd output method\n \
            -n   ----> set cycle times\n \
            -t   ----> set delay_us value\n \
            -h   ----> get help message\n\n \
        eg:\n \
        pwm-led -l xxx       ----> select /sys/class/leds/xxx\n \
        pwm-led -m 1 -t 500  ----> select method 1,and set delay_us = 500us\r\n");
}

int main(int argc, char *argv[])
{
    int fd;
    int len, oc;
    int i = 0, n = 10;
    int max_brightness = DEFAULT_MAX_BRIGHTNESS;
    int method = 0, delay_us = DEFAULT_DELAY_US;
    float val;
    char *arg = NULL, tmp[8] = "0";
#if (JZ_GENERIC_PWM == 1)
    char led[68] = "/sys/class/jz-pwm/";
#else
    char led[68] = "/sys/class/leds/";
#endif

    while(1) {
        oc = getopt(argc, argv, "hl:m:n:t:");
        if(oc == -1)
            break;

        switch(oc) {
        case 'l':
            arg = optarg;
            break;

        case 'm':
            method = atoi(optarg);
            break;

        case 'n':
            n = atoi(optarg);
            break;

        case 't':
            delay_us = atoi(optarg);
            break;

        case 'h':
        default:
            print_usage();
            return 1;
        }
    }

    if(arg != NULL) {
        strcat(led, arg);
        printf("LED name: %s\n", arg);
    } else {
        strcat(led, DEFAULT_LED);
        printf("LED name: %s\n", DEFAULT_LED);
    }

    len = strlen(led);

#if (JZ_GENERIC_PWM == 1)
    strncpy(led + len, "/max_dutyratio", sizeof("/max_dutyratio"));
#else
    strncpy(led + len, "/max_brightness", sizeof("/max_brightness"));
#endif
    fd = open(led, O_RDONLY);
    if(fd != -1) {
        if(read(fd, tmp, sizeof(tmp)) > 0)
            max_brightness = atoi(tmp);
        close(fd);
    }

    printf("        method = %d\n", method);
    printf("      delay_us = %d\n", delay_us);
    printf("max_brightness = %d\n", max_brightness);

#if (JZ_GENERIC_PWM == 1)
    strncpy(led + len, "/dutyratio", sizeof("/dutyratio"));
#else
    strncpy(led + len, "/brightness", sizeof("/brightness"));
#endif
    fd = open(led, O_WRONLY);
    if(fd < 0) {
        printf("Failed to open: %s\n", led);
        return -1;
    }

    while(n--) {
        if(method == 0) {
            for(i = 0; i < sizeof(duty)/sizeof(float); i++) {
                val = max_brightness * duty[i];
                len = snprintf(tmp, sizeof(tmp), "%d", (int)val);

                if(write(fd, tmp, len) < 0) {
                    printf("%d: write failed\n", __LINE__);
                    continue;
                }

                usleep(delay_us);
            }

            for(i = sizeof(duty)/sizeof(float) - 1; i >= 0; i--) {
                val = max_brightness * duty[i];
                len = snprintf(tmp, sizeof(tmp), "%d", (int)val);

                if(write(fd, tmp, len) < 0) {
                    printf("%d: write failed\n", __LINE__);
                    continue;
                }

                usleep(delay_us);
            }
        } else {
            for(val = 0; val < max_brightness; val++) {
                len = snprintf(tmp, sizeof(tmp), "%d", (int)val);

                if(write(fd, tmp, len) < 0) {
                    printf("%d: write failed\n", __LINE__);
                    continue;
                }

                usleep(delay_us);
            }

            for(val = max_brightness; val >= 0; val--) {
                len = snprintf(tmp, sizeof(tmp), "%d", (int)val);

                if(write(fd, tmp, len) < 0) {
                    printf("%d: write failed\n", __LINE__);
                    continue;
                }

                usleep(delay_us);
            }
        }
    }

    close(fd);
    return 0;
}
