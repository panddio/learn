/*************************************************************************
	> Filename: loader.c
	>   Author: 
	>    Email: 
	> Datatime: 2017年02月24日 星期五 22时34分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        FILE *fp;
        FILE *fp_n;
        char *app_buf;
        uint32_t length;

        fp = fopen("./app", "rb");
        if (fp == NULL) {
            printf("Cannot open file!\n");
            return -1;
        }

        fseek(fp, 0, SEEK_SET);
        fread(&length, sizeof(length), 1, fp);
        printf("read length=%d\n", length);

        app_buf = (char *)malloc(length);
        if (app_buf == NULL) {
            printf("Failed to malloc mem\n");
            return -1;
        }
        bzero(app_buf, length);

        fp_n = fopen("./n_app", "ab+");
        if (fp_n == NULL) {
            printf("Cannot open new file!\n");
            return -1;
        }

        fread(app_buf, length, 1, fp);
        fwrite(app_buf, length, 1, fp_n);

        fclose(fp);
        fclose(fp_n);
        free(app_buf);
    } else {
        int fd;
        int fd_n;
        uint32_t length;
        char *app_buf;

        fd = open("./app", O_RDONLY);
        if (fd < 0) {
            printf("Cannot open app file\n");
            return -1;
        }

        read(fd, (void *)&length, sizeof(length));
        printf("read length=%d\n", length);

        app_buf = (char *)malloc(length);
        if (app_buf == NULL) {
            printf("Failed to malloc mem\n");
            return -1;
        }
        bzero(app_buf, length);
        read(fd, app_buf, length);

        fd_n = open("./n_app", O_RDWR | O_CREAT);
        if (fd_n < 0) {
            printf("Cannot open n_app file\n");
            return -1;
        }

        write(fd_n, app_buf, length);
        fsync(fd_n);
        fchmod(fd_n, 0775);

        close(fd);
        close(fd_n);
        free(app_buf);
    }

    return 0;
}
