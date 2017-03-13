/*************************************************************************
	> Filename: main.c
	>   Author: Qiuwei.wang
	>    Email: qiuwei.wang@ingenic.com / panddio@163.com
	> Datatime: Fri 02 Dec 2016 10:54:24 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "common.h"
#include "capture.h"

/*
 * Macro
 */
#define DEFAULT_DEVICE   "/dev/video0"
#define DEFAULT_WIDTH    640
#define DEFAULT_HEIGHT   480
#define DEFAULT_BPP      16
#define DEFAULT_NBUF     1


static const char short_options[] = "d:hmn:rux:y:";

static const struct option long_options[] = {
	{ "device",     1,      NULL,           'd' },
	{ "help",       0,      NULL,           'h' },
	{ "mmap",       0,      NULL,           'm' },
	{ "nbuf",       1,      NULL,           'n' },
	{ "read",       0,      NULL,           'r' },
	{ "userp",      0,      NULL,           'u' },
	{ "width",      1,      NULL,           'x' },
	{ "height",     1,      NULL,           'y' },
	{ 0, 0, 0, 0 }
};

/*
 * Functions
 */
static void usage(FILE *fp, int argc, char *argv[])
{
	fprintf(fp,
			 "\nUsage: %s [options]\n"
			 "Options:\n"
			 "-d | --device name   Video device name [/dev/video]\n"
			 "-h | --help          Print this message\n"
			 "-m | --mmap          Use memory mapped buffers\n"
			 "-n | --nbuf          Request buffer numbers\n"
			 "-r | --read          Use read() calls\n"
			 "-u | --userp         Use application allocated buffers\n"
			 "-x | --width         Capture width\n"
			 "-y | --height        Capture height\n"
			 "\n", argv[0]);
}

int main(int argc, char *argv[])
{
	struct capture_t capt;

	capt.dev_name = DEFAULT_DEVICE;
	capt.width    = DEFAULT_WIDTH;
	capt.height   = DEFAULT_HEIGHT;
	capt.bpp      = DEFAULT_BPP;
	capt.nbuf     = DEFAULT_NBUF;
	capt.io       = IO_METHOD_MMAP;

	while(1) {
		int oc;

		oc = getopt_long(argc, argv, \
						 short_options, long_options, \
						 NULL);
		if(-1 == oc)
			break;

		switch(oc) {
		case 0:
			break;

		case 'd':
			capt.dev_name = optarg;
			break;

		case 'h':
			usage(stdout, argc, argv);
			exit(EXIT_SUCCESS);
			break;

		case 'm':
			capt.io = IO_METHOD_MMAP;
			break;

		case 'r':
			capt.io = IO_METHOD_READ;
			break;

		case 'u':
			capt.io = IO_METHOD_USERPTR;
			break;

		case 'n':
			capt.nbuf = atoi(optarg);
			break;

		case 'x':
			capt.width = atoi(optarg);
			break;

		case 'y':
			capt.height = atoi(optarg);
			break;

		default:
			usage(stderr, argc, argv);
			exit(EXIT_FAILURE);
			break;
		}
	}

	open_device(&capt);
	init_device(&capt);

	test_framerate(&capt);

	start_capturing(&capt);
	main_loop(&capt);
	stop_capturing(&capt);

	free_device(&capt);
	close_device(&capt);

	return 0;
}
