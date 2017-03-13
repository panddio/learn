/*************************************************************************
	> File Name: sound.c
	> Author: 
	> Mail: 
	> Created Time: Tue 06 Sep 2016 05:26:44 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>

#define LENGTH    8      /* 存储秒数 */
#define RATE      16000  /* 采样频率 */
#define BITS      16     /* 量化位数 */
#define CHANNELS  1      /* 声道数目 */

/********以下是wave格式文件的文件头格式说明******/
/*------------------------------------------------
|             RIFF WAVE Chunk                  |
|             ID = 'RIFF'                     |
|             RiffType = 'WAVE'                |
------------------------------------------------
|             Format Chunk                     |
|             ID = 'fmt '                      |
------------------------------------------------
|             Fact Chunk(optional)             |
|             ID = 'fact'                      |
------------------------------------------------
|             Data Chunk                       |
|             ID = 'data'                      |
------------------------------------------------*/
/**********以上是wave文件格式头格式说明***********/
/*wave 文件一共有四个Chunk组成，其中第三个Chunk可以省略，每个Chunk有标示（ID）,大小（size,就是本Chunk的内容部分长度）,内容三部分组成*/
typedef struct waveheader
{
	/****RIFF WAVE CHUNK*/
	unsigned char a[4];//四个字节存放'R','I','F','F'
	long int b;        //整个文件的长度-8;每个Chunk的size字段，都是表示除了本Chunk的ID和SIZE字段外的长度;
	unsigned char c[4];//四个字节存放'W','A','V','E'
	/****Format CHUNK*/
	unsigned char d[4];//四个字节存放'f','m','t',''
	long int e;       //16后没有附加消息，18后有附加消息；一般为16，其他格式转来的话为18
	short int f;       //编码方式，一般为0x0001;
	short int g;       //声道数目，1单声道，2双声道;
	long int h;        //采样频率;
	long int i;        //每秒所需字节数;
	short int j;       //每个采样需要多少字节，若声道是双，则两个一起考虑;
	short int k;       //即量化位数
	/***Data Chunk**/
        unsigned char p[4];//四个字节存放'd','a','t','a'
	long int q;        //语音数据部分长度，不包括文件头的任何部分
} waveheader;//定义WAVE文件的文件头结构体

waveheader *get_waveheader(int bits, int rates, int channels, unsigned long size)
{
    waveheader *header = malloc(sizeof(*header));

	header->a[0] = 'R';
	header->a[1] = 'I';
	header->a[2] = 'F';
	header->a[3] = 'F';
	header->b = size - 8;
	header->c[0] = 'W';
	header->c[1] = 'A';
	header->c[2] = 'V';
	header->c[3] = 'E';
	header->d[0] = 'f';
	header->d[1] = 'm';
	header->d[2] = 't';
	header->d[3] = ' ';
	header->e = 16;
	header->f = 1;
	header->g = channels;
	header->h = rates;
	header->i = size / (rates * channels * bits / 8);
	header->j = channels * bits / 8;
	header->k = bits;
	header->p[0] = 'd';
	header->p[1] = 'a';
	header->p[2] = 't';
	header->p[3] = 'a';
	header->q = size;

    return header;
}

int main(int argc, char *argv[])
{
    unsigned char *buf = NULL, *pbuf = NULL;
    unsigned int size = 0, cnt = 0;
    int len;
    int fd;     /* 声音设备的文件描述符 */
    int arg;    /* 用于ioctl调用的参数 */
    int status; /* 系统调用的返回值 */

    if (argc > 2) {
        printf("Too many arguments!\n");
        exit(1);
    }

    if (argc == 2) {
        /* 打开声音设备 */
        fd = open("/dev/mixer3", O_RDWR);
        if (fd < 0) {
            perror("open of /dev/mixer3 failed");
            exit(1);
        }

        arg = atoi(argv[1]);
        /* set dmix gain */
        status = ioctl(fd, SOUND_MIXER_WRITE_MIC, &arg);
        if(status < 0)
            perror("SOUND_MIXER_WRITE_MIC ioctl failed");

        int vol = 0, left = 0, right = 0;
        /* get dmic gain */
        status = ioctl(fd, SOUND_MIXER_READ_IGAIN, &vol);
        left = vol & 0xff;
        right = vol >> 8;
        printf("left gain id %d %%, right gain is %d %%\n", left, right);
        close(fd);
    }

    /* 打开声音设备 */
    fd = open("/dev/dsp3", O_RDONLY);
    if (fd < 0) {
        perror("open of /dev/dsp3 failed");
        exit(1);
    }

    /* 设置采样时的量化位数 */
    arg = BITS;
    status = ioctl(fd, SNDCTL_DSP_SETFMT, &arg);
    if (status < 0)
        perror("SOUND_PCM_WRITE_BITS ioctl failed");
    if (arg != BITS)
        perror("unable to set sample size");

    /* 设置采样时的声道数目 */
    arg = CHANNELS;
    status = ioctl(fd, SNDCTL_DSP_CHANNELS, &arg);
    if (status < 0)
        perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
    if (arg != CHANNELS)
        perror("unable to set number of channels");

    /* 设置采样时的采样频率 */
    arg = RATE;
    status = ioctl(fd, SNDCTL_DSP_SPEED, &arg);
    if (status < 0)
        perror("SOUND_PCM_WRITE_WRITE ioctl failed");

    /* 用于保存数字音频数据的内存缓冲区 */
    size = LENGTH * RATE * CHANNELS * BITS/8;
    buf = (unsigned char *)malloc(size);
    if(buf == NULL) {
        printf("malloc data buffer failed!\n");
        exit(1);
    }

    printf("Say something now...\n");
    len = read(fd, buf, size);
    if(len != size) {
        perror("read wrong number of bytes");
        exit(1);
    }

    /* make the wav file header */
    waveheader *header = get_waveheader(BITS, RATE, CHANNELS, len);

    /* creat wav file */
    int wav_fd = open("/tmp/record.wav", O_WRONLY | O_CREAT, 0777);

    /* write wav file header */
    write(wav_fd, header, sizeof(*header));
    free(header);
    header = NULL;

    pbuf = buf;
    /* write pcm data */
    while(len > 0) {
        cnt = len > 10240 ? 10240 : len;
        cnt = write(wav_fd, pbuf, cnt);
        if(cnt < 0) {
            printf("write error, retry.\n");
            exit(1);
        }
        len -= cnt;
        pbuf += cnt;
    }

    free(buf);
    close(fd);
    close(wav_fd);
    printf("record done, output file: /tmp/recorder.wav\n");
    return 0;
}
