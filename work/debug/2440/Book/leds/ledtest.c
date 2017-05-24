
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*
  *  ledtest <dev> <on|off>
  */

void print_usage(char *file)
{
    printf("Usage:\n");
    printf("%s <dev> <on|off>\n",file);
    printf("eg. \n");
    printf("%s /dev/leds on\n", file);
    printf("%s /dev/leds off\n", file);
    printf("%s /dev/led1 on\n", file);
    printf("%s /dev/led1 off\n", file);
}

int main(int argc, char **argv)
{
    int fd;
    char* filename;
    char val;

    if (argc != 3)
    {
        print_usage(argv[0]);//当你判断argc!=设定的命令行参数时，你就调print_usage()函数
        return 0;
    }

    filename = argv[1];
/*#include<fcntl.h>
   int open(const char *pathname,int flags);
   int open(const char *pathname,int flags,mode_t mode);
   (第三个参数仅当创建新文件时（即 使用了O_CREAT 时）才使用，
   用于指定文件的访问权限位（access permission bits）。)
   flags 用于指定文件的打开/创建模式
*/
    fd = open(filename, O_RDWR);//打开/创建filename，可读写
    if (fd < 0)
    {
        printf("error, can't open %s\n", filename);
        return 0;
    }

    if (!strcmp("on", argv[2]))
    {
        // 亮灯
        val = 0;
        write(fd, &val, 1);
    }
    else if (!strcmp("off", argv[2]))
    {
        // 灭灯
        val = 1;
        write(fd, &val, 1);
    }
    else
    {
        print_usage(argv[0]);
        return 0;
    }
    
    
    return 0;
}

