/******************************************************************************
  文 件 名   : firewall_file.c
  版 本 号   : 初稿
  作    者   : if
  生成日期   : 2015年9月15日
  最近修改   :
  功能描述   : 将防火墙规则写入文件或从文件读出
  函数列表   :
              filrewall_save_rule
              firewall_config
              firewall_read_rule_file
              firewall_save_all_rules
              firewall_get_passwd
              firewall_save_passwd
  修改历史   :
  1.日    期   : 2015年9月15日
    作    者   : if
    修改内容   : 创建文件

******************************************************************************/
#include "common.h"
#include "route_firewall.h"

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define RULE_FILE    ".firewall_rule"
#define PASSWD_FILE  ".passwd"

/*****************************************************************************
 函 数 名  : firewall_save_all_rules()
 功能描述  : 把防火墙规则链表的所有规则保存到文件
 输入参数  : rt       TYPE_Route 类型结构指针
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void firewall_save_all_rules(TYPE_Route *rt)
{
	FILE *fp = NULL;
	FIRE_Wall *pnode = NULL;
	FIRE_Wall *pbuf[4] = {rt->mac_head,rt->ip_head,rt->port_head,rt->pro_head};
	char rule[RULE_LEN] = "";
	int i = 0;
	
	fp = fopen(RULE_FILE, "wb");

	if(fp != NULL){
		for(i=0; i<4; i++)
		{
			pnode = pbuf[i];

			while(pnode != NULL)
			{
				strcpy(rule, pnode->rule);
				strcat(rule,"\n");
				fwrite(rule, 1, strlen(rule), fp);

				pnode = pnode->next;
			}		
		}
		
		fclose(fp);
	}		
}

/*****************************************************************************
 函 数 名  : filrewall_save_rule()
 功能描述  : 把新加的防火墙规则保存到文件
 输入参数  : rule     要保存的规则
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void filrewall_save_rule(const char *rule)
{
	FILE *fp = NULL;	

	fp = fopen(RULE_FILE, "ab");
	if(fp != NULL){
		char buf[RULE_LEN] = "";

		strcpy(buf, rule);
		strcat(buf, "\n");

		fwrite(buf, 1, strlen(buf), fp);
		fclose(fp);
	}
}

/*****************************************************************************
 函 数 名  : firewall_read_rule_file()
 功能描述  : 读出防火墙规则文件的内容
 输入参数  : file_name       文件名
 返 回 值  : 返回指向文件内容的首部的指针
 修改日期  : 2015年9月15日
*****************************************************************************/
static char *firewall_read_rule_file(const char *file_name)
{
	FILE *fp = NULL;
	char *buf = NULL;
	ulint file_length = 0;

	fp = fopen(file_name, "rb");
	if(fp == NULL){
		//printf("Cannot open the flie!\n");
		//Z文件不存在，则创建，然后返回
		fp = fopen(file_name, "wb");
		fclose(fp);
		return;
	}

	fseek(fp,0,SEEK_END);
	file_length = ftell(fp);
	buf = (char *)malloc(file_length); //动态分配内存

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

/*****************************************************************************
 函 数 名  : firewall_config()
 功能描述  : 读出防火墙规则文件的内容，建立过滤规则链表
 输入参数  : rt       TYPE_Route 类型结构指针
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void firewall_config(TYPE_Route *rt)
{
	char *p_src = NULL;
	char *p_rule= NULL;

	p_src = (char *)firewall_read_rule_file(RULE_FILE);

	p_rule = strtok(p_src, "\n");
	while(p_rule != NULL){
		firewall_build_rule(rt, p_rule, 0);
		p_rule = strtok(NULL, "\n");
	}

	free(p_src);
}

/*****************************************************************************
 函 数 名  : firewall_get_passwd()
 功能描述  : 从文件获取防火墙的密码
 输入参数  : rt       TYPE_Route 类型结构指针
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void firewall_get_passwd(TYPE_Route *rt)
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
		str[i] -= ENCRYPT_KEY;
	}

	strcpy(rt->passwd, str);

	fclose(fp);
}

/*****************************************************************************
 函 数 名  : firewall_save_passwd()
 功能描述  : 防火墙的密码加密后保存到文件
 输入参数  : passwd       要保存的密码
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
void firewall_save_passwd(char passwd[])
{
	FILE *fp = NULL;
	int i, len;

	len = strlen(passwd);

	for(i=0; i<len; i++) {
		passwd[i] += ENCRYPT_KEY;
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

/*****************************************************************************
 函 数 名  : getch()
 功能描述  : 获取一个字符
 输入参数  : NULL
 返 回 值  : NULL
 修改日期  : 2015年9月15日
*****************************************************************************/
static char getch()
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

/*****************************************************************************
 函 数 名  : get_passwd()
 功能描述  : 获取密码
 输入参数  : pwd      保存获取密码的指针
 返 回 值  : max_len  密码的最大长度
 修改日期  : 2015年9月15日
*****************************************************************************/
void get_passwd(char passwd[], int max_len)
{
	char ch = 0, i = 0;
	char buf[PASSWD_LEN];

	while(i < max_len)
	{
		ch = getch();
		if(ch == 10){       // 回车键
			passwd[i] = 0;
			break;
		}
		else if(ch ==127) { // 回格键
			//i--;
			//if(i<0) i = 0;
			continue;
		}
		passwd[i++] = ch;
		putchar('*');
	}

	passwd[max_len] = 0;
}
