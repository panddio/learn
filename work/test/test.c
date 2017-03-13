/* ************************************************************************
 *       Filename:  test.c
 *    Description:
 *        Version:  1.0
 *        Created:  12/03/2015 04:55:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (),
 *        Company:
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>


#if 1

int main(int argc, char argv[])
{
    unsigned long length = 0;
    FILE *fp = NULL;
    char *buf = NULL;

    fp = fopen("./qrcode_app", "rb+");
    if(fp==NULL) {
        printf("Cannot open the file\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);

    printf("file length: %lu\n", length);
    fseek(fp, 0, SEEK_SET);
    fwrite(&length, sizeof(length), 1, fp);

    unsigned long r_len = 0;
    fseek(fp, 0, SEEK_SET);
    fread(&r_len, sizeof(length), 1, fp);
    printf("read length: %lu\n", r_len);

    fclose(fp);
    return 0;
}
#elif 0
int test(char *src, char *dst)
{
    if (src == NULL || dst == NULL)
        return -1;
    int count = 0;
    char *p=NULL;
    p = strtok(src, dst);
    while(p != NULL) {
        count++;
        p = strtok(NULL, src);
    }

    return count;
}

void main()
{
    char *src = "dd23kjdi32kkj23,  423";
    char *buf = src;
    char *dst = "23";
    int count = 0;
    char *p[100];

    printf("src=%s, dst=%s\n", src, dst);
    printf("count=%d\n", count);
    //p[count] = strtok(buf, dst);
    while((p[count] = strtok(buf, "23")) != NULL) {
        count++;
        //p[count] = strtok(buf, dst);
    }
    printf("count=%d\n", count);
}
#elif 0
#include <pwd.h>
static void do_sth(int cnt)
{
    printf("This is a test program: %d!\n", cnt);
}

static void dump_compile_info(void)
{
	time_t timep;
	struct passwd *pwd;
	char hostname[16] = "Unknown";

	time(&timep);
	pwd = getpwuid(getuid());
	gethostname(hostname, 16);
	printf("mozart compiled at %s on %s@%s\n", asctime(gmtime(&timep)), pwd->pw_name, hostname);
}

int main(int argc, char *argv[])
{
    int cnt = 0;
    daemon(0, 1);
    while(1) {
        do_sth(cnt);
        cnt++;
        sleep(1);
        if (cnt > 20)
            break;
    }

    dump_compile_info();
    return 0;
}
#elif 0
struct cim_framebuf {
	unsigned char id;
	unsigned char busy;
	unsigned char *pfree;
	unsigned char *vaddr;
	unsigned char *paddr;
	struct cim_framebuf *next;
};

struct jz_cim_dev {
	unsigned int nbuf;
	unsigned int frame_size;
	unsigned char read_flag;
	unsigned char dma_started;
	struct cim_framebuf *framebuf_head;
	struct cim_framebuf *framebuf_index;
};

struct jz_cim_dev *cim = NULL;

static struct cim_framebuf *cim_insert_link(struct cim_framebuf *head, struct cim_framebuf *in)
{
	struct cim_framebuf *pi, *pb;

	if(in != NULL) {
		pi = in;

		if(head == NULL) {
			head = pi;
			head->next = head;
		} else {
			pb = head;

			while(pb->next != head)
				pb = pb->next;

			pi->next = head;
			pb->next = pi;
		}
	}

	return head;
}

static struct cim_framebuf *cim_free_link(struct cim_framebuf *head)
{
	struct cim_framebuf *pb, *pn;

	if(head != NULL) {
		pb = head;
		pn = head->next;

		while(pn != head) {
			free(pb->pfree);
			free(pb);

			pb = pn;
			pn = pn->next;
		}

		/* Last node */
		free(pb->pfree);
		free(pb);
	}

	return NULL;
}

void cim_print_link(struct cim_framebuf *head)
{
	struct cim_framebuf *pb;
	if(head != NULL) {
		pb = head;
		printf("pb->id = %d\n", pb->id);
		printf("cim->framebuf vaddr = 0x%08x\n", pb->vaddr);
		printf("cim->framebuf paddr = 0x%08x\n", pb->paddr);

		while(pb->next != head) {
			pb = pb->next;
			printf("pb->id = %d\n", pb->id);
			printf("cim->framebuf vaddr = 0x%08x\n", pb->vaddr);
			printf("cim->framebuf paddr = 0x%08x\n", pb->paddr);
		}
	}
}

static int cim_fb_malloc(struct jz_cim_dev *cim)
{
	int i;
	struct cim_framebuf *in;

	for(i = 0; i < cim->nbuf; i++) {
		in = (struct cim_framebuf *)malloc(sizeof(struct cim_framebuf));
		if(!in) {
			printf("Can nor apply a framebuf memory space!\n");
			return -1;
		}

		in->vaddr = (unsigned char *)malloc(cim->frame_size + 0x3f);
		if(!in->vaddr) {
			printf("malloc framebuf failed\n");
			return -1;
		}

		memset(in->vaddr, 0, cim->frame_size);
		in->id = i;
		in->pfree = in->vaddr;
		in->paddr = in->vaddr + 0x01;

		printf("cim->framebuf vaddr = 0x%08x\n", in->vaddr);
		printf("cim->framebuf paddr = 0x%08x\n", in->paddr);
		cim->framebuf_head = cim_insert_link(cim->framebuf_head, in);
	}

	cim->framebuf_index = cim->framebuf_head;

	return 0;
}

static void cim_fb_free(struct jz_cim_dev *cim)
{
	cim->framebuf_head = cim_free_link(cim->framebuf_head);
}

int main(int argc, char *argv[])
{
	int count;
	cim = (struct jz_cim_dev *)malloc(sizeof(struct jz_cim_dev));
	if(!cim) {
		printf("%s -- malloc cim dev failed\n", __FUNCTION__);
		return -1;
	}

	memset(cim, 0, sizeof(struct jz_cim_dev));

	cim->nbuf = 1;
	cim->frame_size = 640 * 480 * 2;

	cim_fb_malloc(cim);

	count = 4;
	while(count--)
		cim_print_link(cim->framebuf_head);

	cim->nbuf = 3;
	cim_fb_free(cim);
	cim_fb_malloc(cim);
	printf("====================================\n");
	count = 25;
	while(count--) {
		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
		printf("cim framebuf id = %d\n", cim->framebuf_index->id);
		printf("cim->framebuf vaddr = 0x%08x\n", cim->framebuf_index->vaddr);
		printf("cim->framebuf paddr = 0x%08x\n", cim->framebuf_index->paddr);
		cim->framebuf_index = cim->framebuf_index->next;
		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	}

	return 0;
}
#elif 0

struct img_param_t {
	unsigned int width;      /* width */
	unsigned int height;     /* height */
	unsigned int bpp;        /* bits per pixel: 8/16/32 */
};

struct timing_param_t {
	unsigned long mclk_freq;
	unsigned int pclk_active_level;  //0 for rising edge, 1 for falling edge
	unsigned int hsync_active_level;
	unsigned int vsync_active_level;
};

struct pix_buffer_t {
	int read_flag;
	void *pbuf;              /* point to a frame_size buffer */
};

struct get_frame_t {
	unsigned int nbuf;       /* buffer number */
	unsigned int frame_size; /* frame image size */
	struct pix_buffer_t pix[0];
};

struct jz_cim_dev {
    unsigned int frame_size;
    unsigned char read_flag;
    unsigned char dma_started;
    unsigned char *pframebuf;
    unsigned char *framebuf_vaddr;
    unsigned char *framebuf_paddr;
    void *desc_vaddr;
    struct cim_dma_desc *dma_desc_paddr;
    struct img_param_t img;
    struct timing_param_t timing;
    struct get_frame_t *frame;
};

int main(int argc, char *argv[])
{

    printf("sizeof(long) = %lu\n", sizeof(long));
    printf("sizeof(void *) = %lu\n", sizeof(void *));
    printf("sizeof(struct img_param_t) = %lu\n", sizeof(struct img_param_t));
    printf("sizeof(struct timing_param_t) = %lu\n", sizeof(struct timing_param_t));
    printf("sizeof(struct pix_buffer_t) = %lu\n", sizeof(struct pix_buffer_t));
    printf("sizeof(struct get_frame_t) = %lu\n", sizeof(struct get_frame_t));
    printf("sizeof(struct jz_cim_dev) = %lu\n", sizeof(struct jz_cim_dev));

    return 0;
}

#elif 0
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
typedef unsigned char u8;
typedef unsigned long u32;

struct regval_list {
	u8 reg_num;
	u8 value;
};

struct mode_list {
	u8 index;
	const struct regval_list *mode_regs;
};

/* Supported resolutions */
enum gc2155_width {
	W_QVGA	= 320,
	W_VGA	= 640,
	W_720P  = 1280,
};

enum gc2155_height {
	H_QVGA	= 240,
	H_VGA	= 480,
	H_720P  = 720,
};

struct gc2155_win_size {
	char *name;
	enum gc2155_width width;
	enum gc2155_height height;
	const struct regval_list *regs;
};

#define GC2155_SIZE(n, w, h, r) \
	{.name = n, .width = w , .height = h, .regs = r }

static const struct gc2155_win_size gc2155_supported_win_sizes[] = {
	GC2155_SIZE("QVGA", W_QVGA, H_QVGA, NULL),
	GC2155_SIZE("VGA", W_VGA, H_VGA, NULL),
	GC2155_SIZE("720P", W_720P, H_720P, NULL),
};

/* Select the nearest higher resolution for capture */
static const struct gc2155_win_size *gc2155_select_win(u32 *width, u32 *height)
{
	int i, default_size = ARRAY_SIZE(gc2155_supported_win_sizes);

	for (i = 0; i < default_size; i++) {
		if (gc2155_supported_win_sizes[i].width  >= *width &&
		    gc2155_supported_win_sizes[i].height >= *height) {
			*width = gc2155_supported_win_sizes[i].width;
			*height = gc2155_supported_win_sizes[i].height;
			return &gc2155_supported_win_sizes[i];
		}
	}

	*width = gc2155_supported_win_sizes[default_size-1].width;
	*height = gc2155_supported_win_sizes[default_size-1].height;
	return &gc2155_supported_win_sizes[default_size-1];
}

void fun1(int val)
{
	printf("val = %d\n", val);
	val = val + 100;

	printf("val = %d\n", val);

	if(val)
		goto error;

error:
	printf("%s: Error\n", __FUNCTION__);

}
void fun2(int val)
{
	if(val)
		goto error;

error:
	printf("%s: Error\n", __FUNCTION__);

}

void main(void)
{
	u32 width = 340, height = 500;

	struct gc2155_win_size *win = NULL;

	win = (struct gc2155_win_size *)malloc(sizeof(struct gc2155_win_size));

	//win->width = 320;
	//win->height = 240;

	printf("win->width: %d  win->height: %d\n", win->width, win->height);
	win = gc2155_select_win(&width, &height);
	printf("width: %d  height: %d\n", width, height);
	printf("win->width: %d  win->height: %d\n", win->width, win->height);
	fun1(1);
	fun2(2);
}
#elif 0
int main()
{
    int i;
    int val = 0x12345678;
    char buf[4] = "";

    *(int *)buf = val;

    for(i = 0; i <4; i++) {
        printf("buf[%d] = %d\n", i, buf[i]);
    }
}

#elif 0
int main(int argc, char *argv[])
{
	unsigned int val = 0;
	printf("## argc[1] = %s\n", argv[1]);

	val = atoi(argv[1]);
	printf("## atoi(): val = 0x%08x \n",val);

	sscanf(argv[1],"%x", &val);
	printf("## sscanf(): val = 0x%08x \n", val);
	return 0;
}
#elif 0
int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	char *optstring = "a:b:c:d";

	static struct option long_options[] = {
		{"reqarg", required_argument, NULL, 'r'},
		{"nonarg",no_argument, NULL, 'n'},
		{"optarg", optional_argument, NULL, 'o'},
		{0,0,0,0},
	};

	while((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
		printf("opt = %c\n", opt);
		printf("optarg = %s\n", optarg);
		printf("optind = %d\n",optind);
		printf("argv[optind - 1] = %s\n", argv[optind -1]);
		printf("option_index = %d\n", option_index);
	}

	return 0;
}
#elif 0

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[])
{
    int opt;
    char *optstring = "a:b:c:d";

     while ((opt = getopt(argc, argv, optstring)) != -1)
     {
         printf("opt = %c\n", opt);
         printf("optarg = %s\n", optarg);
         printf("optind = %d\n", optind);
         printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]);
    }

    return 0;
}

#elif 0

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, arg...) \
		printf("jz-cim: "fmt, ##arg)
#else
#define debug(fmt, arg...)
#endif

#if 0
#ifdef DEBUG
#define _DEBUG 1
#define debug(fmt, arg...) \
    do {                   \
        if(_DEBUG)         \
		    printf("jz-cim: "fmt, ##arg); \
    }while(0)
#else
#define _DEBUG 0
#define debug(fmt, arg...)       \
    do {                         \
        if(_DEBUG)               \
		    printf("jz-cim: "fmt, ##arg); \
    }while(0)
#endif
#endif

int  main(int argc, char *argv[])
{
	int i = 100;
    debug("=== Hello world --%d ===\n", i);
    return 0;
}
#elif 0
typedef struct {
    int a;
    short s[2];
}MSG;

void main() {
    MSG *mp, m = {4, 1, 256};
    char *fp, *tp;

    mp = (MSG *)malloc(sizeof(MSG));
    for(fp=(char *)mp->s, tp=(char *)m.s; fp < (char *)(mp + 1);) {
        //*fp++ = *tp++;
        *fp = *tp;
        printf("*fp = %d  *tp = %d\n", *fp, *tp);
        fp++;
        tp++;
    }
}
#elif 0

#if 0
The passwd structure is defined in<pwd.h>asfollows:
struct passwd {
	char*pw_name; /*user name */
	char*pw_passwd; /*user password */
	uid_t pw_uid; /*user id */
	gid_t pw_gid; /*group id */
	char*pw_gecos; /*real name */
	char*pw_dir; /*home directory */
	char*pw_shell; /*shell program */
};
#endif
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
int main()
{
	time_t timep;
	struct tm *lct, *gmt;
	struct passwd *pwd;
	char hostname[64] = "Unknown";

	time(&timep);
	lct = localtime(&timep);
	gmt = gmtime(&timep);

	pwd = getpwuid(getuid());
	gethostname(hostname, 16);

	printf("system localtime: %s\n", asctime(lct));
	printf("system gmtime: %s\n", asctime(gmt));
	printf("hostname: %s\n", hostname);
	printf("pw_name: %s\n", pwd->pw_name);
	printf("pw_passwd: %s\n", pwd->pw_passwd);
	printf("pw_uid: %d\n", pwd->pw_uid);

	return 0;
}

#elif 0
int main()
{
    if(daemon(1,0) != 0) {
        perror("daemon");
        return -1;
    }
    int i;
    for(i = 0; i < 5; i++) {
        printf("this is a test\n");
    }

    return 0;
}
#elif 0
int fun(int a)
{
	return a != 0;
}
void main()
{
	printf("ret = %d\n",fun(1));
}
#elif 0
#define A
#define B
int main()
{

#ifndef A
#ifdef B
	printf("defined B\n");
#endif
#endif

#ifdef A
	printf("defined A\n");
#endif
	return 0;
}
#endif

