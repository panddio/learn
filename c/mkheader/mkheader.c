/*************************************************************************
	> Filename: god.c
	>   Author: 
	>    Email: 
	> Datatime: 2017年02月24日 星期五 22时23分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    uint32_t length;
    char *buf;

    //fp = fopen("./app", "rb+");
    fp = fopen(argv[1], "rb+");
    if (fp == NULL) {
        printf("Cannot open the file!\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    printf("write length=%d\n", length);
    buf = (char *)malloc(length + 4);
    if (buf == NULL) {
        printf("Failed to malloc mem\n");
        return 0;
    }
    bzero(buf, length + 4);

    *(uint32_t *)buf = length;

    fseek(fp, 0, SEEK_SET);
    fread(buf+4, length, 1, fp);

    fseek(fp, 0, SEEK_SET);
    fwrite(buf, length + 4, 1, fp);

    fclose(fp);
    return 0;
}
