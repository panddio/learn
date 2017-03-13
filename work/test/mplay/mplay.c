/*************************************************************************
	> File Name: mplay.c
	> Author:
	> Mail:
	> Created Time: Thu 13 Oct 2016 11:29:59 AM CST
 ************************************************************************/

#include <tinyalsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/input.h>


#define PARENT  SIGUSR1
#define CHILD   SIGUSR2

int exit_flag = 1;
int close_flag = 1;
void play_sample(char *filename, unsigned int device);

/*
 * Functions
 */
void signal_handler(int signo)
{
	switch(signo) {
	case SIGINT:
		printf("recv SIGINT\n");
		close_flag = 1;
		break;

	case SIGCHLD:
		printf("recv SIGCHLD\n");
		waitpid(-1, NULL, WNOHANG); // recycling child process
        exit_flag = 1;
		break;
	}
}

int main(int argc, char *argv[])
{
	pid_t pid = -1;
	int ret = 0;
	int keyfd = 0;
	char *filename = NULL;
	struct input_event event;

	keyfd = open("/dev/input/event0", O_RDONLY);
	if(keyfd < 0) {
		printf("open /dev/input/event0 device failed\n");
		return -1;
	}

	if(argc == 2)
		filename = argv[1];
	else
		filename = "/tmp/paomo.wav";

	//注册父进程 SIGCHLD 信号处理函数，用于非阻塞回收子进程
	//SIGCHLD 将在子进程exit()时发给父进程
	signal(SIGCHLD, signal_handler);

	while(1) {
		bzero(&event, sizeof(struct input_event));
		ret = read(keyfd, &event, sizeof(struct input_event));

		if(ret == sizeof(struct input_event)) {
			if(event.type == EV_KEY) {
				printf("key %d -- %s\n", event.code, !event.value? "Pressed" : "Released");

				if(event.code == KEY_POWER) {
					if(event.value == 0) {
						if(pid != -1) {
							kill(pid, SIGINT);
							pid = -1;
						}

                        if(exit_flag) {
                            pid = fork();
                            if(pid < 0) {
                                perror("fork()");
                                break;
                            }

                            exit_flag = 0; // fork() succeed

                            if(pid == 0) {
                                //close_flag = 0;

                                //注册子进程 SIGINT 信号处理函数
                                //SIGINT 在父进程收到新命令时调用kill(pid, SIGINT)时发出
                                //signal(SIGINT, signal_handler);
                                play_sample(filename, 0);

                                #if 0
                                while(!close_flag) {
                                    printf("child process: wait a common!\n");
                                    sleep(1);
                                }
                                #endif
                                printf("child process %d: exit\n", getpid());
                                exit(0); // child process exit
                            }
                        }
                    }
				}
			}
		}
	}

	close(keyfd);
    return 0;
}
