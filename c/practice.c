/* ************************************************************************
 *       Filename:  studer_score.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年07月20日 星期一 11時04分43秒 HKT
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>

#if 0
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

		while(pb->next != head) {
			pb = pb->next;
			printf("pb->id = %d\n", pb->id);
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
		in->paddr = in->vaddr;

		if((unsigned int)in->paddr & 0x3f) { // Not aligned
			in->paddr += ((unsigned int)in->paddr / 128 + 1) * 128 - (unsigned int)in->paddr;
			in->vaddr += ((unsigned int)in->vaddr / 128 + 1) * 128 - (unsigned int)in->vaddr;
		}

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
	cim = (struct jz_cim_dev *)malloc(sizeof(struct jz_cim_dev));
	if(!cim) {
		printf("%s -- malloc cim dev failed\n", __FUNCTION__);
		return -1;
	}

	memset(cim, 0, sizeof(struct jz_cim_dev));

	cim->nbuf = 3;

	cim_fb_malloc(cim);
	cim_print_link(cim->framebuf_head);
	return 0;
}
#elif 0
#include "console.h"

static char getch() 
{
    struct termios oldt, newt;
    char ch;
        
    tcgetattr( STDIN_FILENO, &oldt  );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO  );
        
    tcsetattr( STDIN_FILENO, TCSANOW, &newt  );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt  );
        
    return ch;
}


void main()
{
    int i, j;
    char ch;
    char buf[PASSWD_LEN] = {0};
    char passwd[PASSWD_LEN] = {0};

    cusor_get_pos();
    for(i = 0; i < PASSWD_LEN; i++){
        ch = getch();
        if(ch == 10){       // 回车键
            passwd[i] = 0;
            break;
        }
        else if(ch ==127) { // 回格键
            i--;
            if(i < 0)
                i = 0;
            passwd[i] = 0;
            buf[i] = 0;
        }
        else {
            passwd[i] = ch;
            buf[i] = '*';
        }
        cusor_set_pos();
        for(j = 0;j < PASSWD_LEN; j++)
            putchar(buf[j]);
    }
    putchar('\n'); 

}
#elif 0
/************************************************************************/
/* 把所有的奇数放到所有偶数的前面                                                                     */
/************************************************************************/
void reverseString(char *p)
{
	//char *ptr=p;
	if( *p == '\0' || *(p + 1) == '\0' ) 
	{
		return ;
	}
	else 
	{
		reverseString(p+1);
		if(*p%2 == 0)
		{
			while( *(p + 1) != '\0' )
			{
		//	if (*p%2 == 0)
			{
				*p = *(p + 1) ^ *p;
				*(p + 1) = *p ^ *(p + 1);
				*p = *p ^ *(p + 1);
			
			}/*	
				*p = *(p+1) + *p;
				*(p+1) = *p - *(p+1);
				*p = *p - *(p+1);*/
				p++;
			}
		}
		//reverseString(p + 1);
	}
    
	return ;
}

int main(int argc, char *argv[])
{
	//int i;
	char str[] = "1234567";
	reverseString(str);
	//for(i = 0; i < 4; i++)
	    printf("%s",str);
	
	return 0;
}
#elif 0
#define PASSWD_FILE  ".passwd"
#define PASSWD_LEN    9

void firewall_get_passwd(char passwd[])
{
	FILE *fp = NULL;
	char str[PASSWD_LEN] = "";
	int i, len;

	fp = fopen(PASSWD_FILE, "rb");
	if(fp == NULL) {
		//文件不存在，则创建，然后退出
		fp = fopen(PASSWD_FILE, "wb");
		fclose(fp);
		return;
	}

	len = fread(str, 1, PASSWD_LEN, fp); //fread 返回实际读的块数
	len--;
	str[len] = 0; // 去掉 \n

	for(i=0; i<len; i++) {
		str[i] -= 22;
	}	
	
	strcpy(passwd, str);
	
	fclose(fp);
}

void firewall_save_passwd(char passwd[])
{
	FILE *fp = NULL;
	int i, len;

	len = strlen(passwd);
	
	for(i=0; i<len; i++) {
		passwd[i] += 22;
	}

	if(len >= PASSWD_LEN) {
		len = PASSWD_LEN-1;
		passwd[len] = 0;
	}
	strcat(passwd,"\n");
	
	fp = fopen(PASSWD_FILE, "wb");
	if(fp != NULL) {
		fwrite(passwd, 1, len+1, fp);
		fclose(fp);
	}	
}

char getch() 
{
    struct termios oldt, newt;
    char ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
void get_passwd(char *pwd, int len)
{
	char ch;
	char i =0;
	while(i<len)
	{
		ch = getch();
		if(ch == 10){
			pwd[i] = 0;
			break;
		} 
		pwd[i++] = ch;

		putchar('*');
	}
}
void main()
{
#if 0	
	char passwd[PASSWD_LEN] = "";
	
	get_passwd(passwd, PASSWD_LEN);
	printf("\n-1-  %s\n",passwd);

	firewall_save_passwd(passwd);
	bzero(passwd, PASSWD_LEN);
	
	firewall_get_passwd(passwd);
	printf("-2-  %s\n",passwd);
#elif 1
	char str[50] = "";
	char ip[16] = "10.221.2.221";
	char mac[18] = "00:0c:67:fa:c6:1d";
	
	sprintf(str,"%12s\n%-18s\n", ip, mac);
	
	printf("%s", str);
	// char ch = getch();
	// printf("%d\n",ch);
	// putchar('*');
	// printf("entry:");
	// ch = getch();
	//gets(str);
#endif
}
#elif 0
void main(int argc)
{
	int ii = 1555444;
	char buf[20];

	sprintf(buf,"%d",ii);
	printf("%s\n",buf);
	
	printf("argc = %d\n",argc);
	
}
#elif 0

char *read_firewall_rule_file(const char *file_name)
{
	FILE *fp = NULL;
	char *buf = NULL;
	int file_length = 0;
	
	fp = fopen(file_name, "rb");
	if(fp == NULL){
		printf("Cannot open the flie!\n");
		return;
	}
	
	fseek(fp,0,SEEK_END);
	file_length = ftell(fp); 	
	buf = (char *)malloc(file_length); //
	
	if(buf == NULL){
		printf("malloc() cannot apply for memory!\n");
		goto out;
	}
	rewind(fp); //
	fread(buf,file_length,1,fp);
	
	out:
	fclose(fp);
	return buf;
}

void main()
{
	char *pbuf = NULL;
	char *p = NULL;
	
	pbuf = read_firewall_rule_file("mac_rule");
	
	printf("buf >>\n%s<<\n", pbuf);
	
	p = strtok(pbuf,"\n");
	while(p != NULL){
		printf("%s $$$len=%d\n",p, strlen(p));
		p = strtok(NULL,"\n");
	}
	free(pbuf);
}
#elif 0
void main()
{
	FILE *fp = NULL;
	char rule[32] = "";
	int i = 0;
	fp = fopen("mac_rule", "ab");
	
	for(i=0;i<3;i++)
	{
		fgets(rule, 32, stdin);
		rule[strlen(rule) - 1] = 0;
		strcat(rule,"\n");
		fwrite(rule,1, strlen(rule), fp);
	}
}
#elif 0

void main()
{
	printf("\033[35;4mhello\033[47;34m world\033[0m\n");
}

#elif 0
char *read_src_file(int *file_length, char *lrc_src)
{
	FILE *fp = NULL;
	char *buf = NULL;
	
	//unsigned long int file_length = 0;
	
	fp = fopen(lrc_src,"rb");//以只读方式打开一个二进制文件
	
	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return;
	}
	fseek(fp,0,SEEK_END);
	*file_length = ftell(fp); //获取文件的大小
	
	buf = (char *)malloc(*file_length); //
	rewind(fp); //
	fread(buf,*file_length,1,fp);
	
	fclose(fp);
	return buf;
}
int src_segment(char *psrc, char *pbuf[], char *str)
{
	int i = 0;
	
	pbuf[0] = strtok(psrc, str);
	
	while(pbuf[i++] != NULL)
	{
		pbuf[i] = strtok(NULL, str);
	} 
	//printf("i=%d\n",i);
	return (i-1);
}
int check_lines(int file_length, char *lrc_src)
{
	int lines = 0;
	int i = 0;
	char *p = NULL;
	
	p = lrc_src;
	
	#if 1
	for(i = 0;i < file_length;i++)
	{
		if(p[i]=='\n')  lines++;
	}
	#elif 0 //这种方法不行，因为strchr函数和strstr函数遇到 '\0' 就返回
	while(p != NULL)
	{
		p = strchr(p,'\n');
		lines++;
	}
	#endif
	return lines;
}
void main()
{
	FILE *fp =NULL;
	char *buf = NULL, *pbuf[100] = {NULL};
	int file_length = 0, i = 0, n = 0;
	int lines = 0;
	system("ls ./lrc2/music | grep .mp3 >./lrc2/.msgbuf");
	
	fp = fopen("lrc2/.msgbuf","rb");
	if(fp == NULL)
	{
		printf("Cannot open the flie!\n");
		return;
	}
	buf = read_src_file(&file_length,"lrc2/.msgbuf");
	lines = check_lines(file_length,buf);
	printf("%d\n",lines);
	
	n = src_segment(buf, pbuf, "\r\n");
	printf("n = %d\n",n);
	for(i=0;i<n-1;i++)
	{
		printf("%s\n",pbuf[i]);
	}
}
#elif 0

int get_chrnumber(char *pbuf, int len)
{
	int i = 0,count = 0;
	
	for(i=0;i<len;i++)
	{
		if(pbuf[i] > 0 && pbuf[i] <127) count++;
	}
	return count;
}

int main()
{
	char str1[100]=" dd笑gh声 喜!!?%欢你  更  迷人g";
	int len = strlen(str1);
	int count = 0;
	
	system("dir >./test.txt");
	count = get_chrnumber(str1,len);
	printf("len=%d\n",len);
	printf("%d\n",count);
	return 0;
}
#elif 0
int main()
{
	char str1[20]="hello \r\nr $#$ world";
	char ch='\n';
	char str2[20]="$#$";
	char *result;
	
	result=strchr(str1,ch);		
	printf("%s\n",result);
	printf("%d\n",result-str1);
	
	result=strstr(str1,str2);		
	printf("%s\n",result);
	printf("%d\n",result-str1);
	return 0;
}
#elif 0 

void main()
{
	char buf[1000] = "这是个测试";
	int count = 0;
	FILE *fp = NULL;

	fp = fopen("love.lrc","rb");

		printf("%s\n",buf);
	if(fp = NULL)
	{
	//	puts("error\n");
		return;
	}
	while(1)
	{
		fgets(buf,100,fp);
		if(feof(fp) != 0)
			break;
		printf("%s\n",buf);
		count++;	
	}

	printf("count=%d\n",count);
	free(fp);
}
#elif 0
void main()
{
	char *p = "hello";
	char *q = "world";
	char **pp;

	pp = (char **)malloc(20);
	
	pp[0]= p;
	pp[1] = q;

	printf("%s %s\n",pp[0],pp[1]);
}
#elif 0
int main()
{
	struct A
	{
		char e;
		short f;
	};
	
	struct B
	{
		int a;
		char b;
		struct A c;
		char d;
	}cc;
	
	printf("%u %u\n",&cc.c.e,&cc.d);

}
#elif 0
struct A
{
	int a;
	double b;
	float c;
};
struct
{
	char e[2];
	int f;
	double g;
	short h;
	struct A i;
}B;

void main()
{
	printf("%d\n",sizeof(B));
}
#elif 0
typedef struct stu
{
	int num;
	char name[20];
	float score;
}STU;
void main()
{
	STU stu[3];
	int i=0;
	float temp = 0;
	float ave = 0.0f;
	for(i=0;i<3;i++)
	{
		printf("请输入%d位学生的学号、姓名、成绩：\n",i+1);
		scanf("%d %s %f",&stu[i].num,stu[i].name,&stu[i].score);
	}

	for(i=0;i<3;i++)
	{
		ave +=stu[i].score;
		//printf("num=%d, name=%s, score=%.1f\n",stu[i].num,stu[i].name,stu[i].score);
	}
	ave /=3;
	printf("平均成绩%.1f\n",ave);
	temp = stu[0].score>stu[1].score?(stu[0].score>stu[2].score?stu[0].score:stu[2].score) 
	     : (stu[1].score>stu[2].score?stu[1].score:stu[2].score);
	printf("最大成绩为%.1f\n",temp);
}

#elif 0
void main()
{
	char buf[128] = "abcfff#degghgf#ghi";
	char buf1[123] = "";
	char m[10] = "",s[10] = "";
	int aminute=0,second=0;

	sscanf(buf,"%*[^#]#%[^#]",buf1); //当buf第一个字符是'#'时，这样取会出错
	printf("buf1=%s\n",buf1);
	
	sscanf("thj[i:简单爱]","%*[^:]%*1s%[^]]",buf1);
	printf("buf1=%s\n",buf1);

	//sscanf("[02:06.85]","%*[[]%2d%*1s%2d",&aminute,&second);
	sscanf("[02:06.85]","[%2d:%2d",&aminute,&second);
	printf("aminute=%d,second=%d\n",aminute,second);
	
	sscanf("[12:16.85]","%*[[]%2d%*[:]%2d",&aminute,&second);
	printf("aminute=%d,second=%d\n",aminute,second);
	
	sscanf("[02:06.85]","%*[[]%2s%*1s%2s",m,s);
	printf("m=%s,s=%s\n",m,s);
}

#elif 0

void main()
{
	char buf[128] = "12345678";
	int a=0,b=0;

	sscanf(buf,"%*2d%2d%*2d%2d",&a,&b);

	printf("a=%d,b=%d\n",a,b);
}

#elif 0

void main()
{
	char dst[40] = "szsunplusedu.com";
	char *p = NULL;

	p = dst;

#elif 0
	while(1)
	{
		p = strchr(p, 'u');

		if(p != NULL)
		{
			*p = '#';
		}
		else
		{
			break;
		}
	}

	printf("%s\n",dst);
}
#elif 0

#define MIN(a,b) ((a)<(b)?(a):(b))
void main()
{
	int a[3]={2,6,8};
	int b = 3;
	int *p  = a;	
	printf("%d\n",MIN(*p++,b));
}
#elif 0
int main(int argc, char *argv[])
{
	float a[5][3]={{80,75,56},{59,65,71},{59,63,70},{85,75,90},{76,77,45}};
	int i,j ,person_low[5]={0};
	float s=0,lesson_aver[5]={0};

	for(j=0;j<5;j++)
	{
		for(i=0;i<3;i++)
		{
			s += a[j][i];
			
			if(a[j][i]<60)
			{
				person_low[j]++;
			}
		
		}
		lesson_aver[j] = s/3;
		s = 0;
	}

	for(i=0;i<5;i++)
	{
		printf("第%d个人的各科平均成绩为：%.2f,不及格有%d科\n",i,lesson_aver[i],person_low[i]);
	}
	return 0;
}
#elif 0

typedef struct game
{
	//struct game *head;
	char *topic;
	char *key;
	struct game *next;
}GAME;

int main(int argc, char *argv[])
{
	GAME one,two,*p;
	char ch[100]={0};

	one.topic = "这是个测试";
	one.key = "12";

	two.topic = "这依然是测试";
	two.key = "13";
	printf("%d\n",sizeof("哈共和斤斤计较哈哈"));
	one.next = &two;
	two.next = &one;
	p = &one;

	do
	{
		sleep(2);
		printf("%s  %s\n",p->topic,p->key);
		p = p->next;
	}while(p != NULL);

	printf("%s %s\n",one.topic,one.key);
	return 0;
}
#elif 0

void main()
{
	int a = 0x01020304;
	int *p = NULL;
	int *cp= NULL;
	char ch = 97;
	cp =&ch;
	cp = (char *)cp;//cp 还是指向int型，有cp定义类型决定
	p = &a;
	printf("%d\n",*(char *)cp);
	printf("0x%x\n",*(short int *)cp);

//	printf("0x%x\n",*((short int *)((char *)p+1)));

}

#elif 0

int sum(int n)
{
	int temp = 0;
	int i;
	if(n==1)
	{
		return 1;
	}
	else if(n>1)
	{
		for(i=1;i<=n;i++)
		{
			temp +=i;
		}
	//	temp +=sum(n-1);
	//	return temp;
		return temp+sum(n-1);
	}
	//return temp;
}
void main()
{
	int n = 0;
	n= sum(6);

	printf("%d\n",n);
}


#elif 0

void main()
{
	int num[5] = { 1,2,3,4,5};
	//int *p[5] = {&num[0],&num[1],&num[2],&num[3],&num[4]};
	int *p[5] = { &num[0]};
	//printf("%d\n",*p[2]);
	printf("%d\n",*(p[0]+2));

	char *str[100] = {"hehe1","hehe2","hehe3","hehe4"};
	char i;

	i = 0;
	while(str[i] != NULL)
	{
		printf("%s\t",str[i]);
		i++;
	}
	putchar('\n');
}
#elif 0
int f(char *s)
{
	char *p=s;
	while(*p!='\0') 
	{
		p++;
	}
	return(p-s);
}

int bic(int d, int m)
{

	char temp_1[32],temp_2[32];
	int i=0,j=0;

	memset(temp_1,'\0',sizeof(temp_1));
	while(d!=0)
	{
		temp_1[i++]=d%2;
		//printf("%c  ",temp_1[i-1]+'0');
		d=d/2;
	}

	memset(temp_2,'\0',sizeof(temp_2));
	i=0;
	while(m!=0)
	{
		temp_2[i++]=m%2;
		m=m/2;
	}


	for(i=0;i<32;i++)
	{
		if(temp_2[i]==1)
		{
			temp_1[i]=0;
		}
		
	}
	d=0;
	for(i=0;i<32;i++)
	{
		d+= temp_1[i]*pow(2,i);
	}
	
	return d;
}

main()
{
	int t;
	t = bic(30,5);
	printf("%d\n", t);

	printf("%d\n",f("FUJIAN"));	
	
}

#elif 1
int main()
{
	char buf[]="I am a good programer, am i? hello, world.";
	//			?i am ,programer good a am i
    //char buf[]="dhhd23jd32kk5623.  6323";
	char * p[50],ch,*str;
	int i=0,j=0,word_num=0;
	printf("***%s***\n",buf);
	str=(char *)malloc(strlen(buf)+1);
	p[i]=strtok(buf," ");//按空格切割字符串
	while(p[i]!=NULL)
	{
		i++;
		p[i]=strtok(NULL," ");
	}
	word_num=i;

#if 1
    printf("word_num=%d\n", word_num);
    for(i = 0; i < word_num; i++) {
        printf("p[%d]=%s\n", i, p[i]);
    }
#else
	for(i=0; i< word_num; i++)//把所有单词中有标点符号的处理完
	{
		if(ispunct( *(p[i]+strlen(p[i])-1)) != 0) //检查参数是否为标点符号或特殊符号，是，返回TRUE
		{
			ch=*(p[i]+strlen(p[i])-1);
			for(j=strlen(p[i]);j>1 ;j--)
			{
				*(p[i]+j-1)=*(p[i]+j-2);
			}
			*p[i]=ch;
		}
	}
	i=word_num;
	strcpy(str,p[i-1]);
	for(i=word_num-2; i>=0  ;i--)//从后向前把所有字符串追加进来，以空格分开
	{
		strcat(str," ");
		strcat(str,p[i]);			
	}

	strcpy(buf,str);
	printf("***%s***\n",buf);
#endif
	free(str);
	return 0;
}
#elif 0
int lenght(char *p)
{
	int len=0;
	len = strlen(p);
	return len;
}
void main()
{
	int aa = 0;
	long bb = 0;
	
	scanf("%2d%ld",&aa,&bb);
	printf("add = %ld\n", aa+bb);
	
	char a[5]={'a','b','c','d','e'};
	//char a[]="abcde";
	printf("%d\n",lenght(a));
}
#endif
