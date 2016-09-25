/******************************************************************************
  �� �� ��   : firewall_file.c
  �� �� ��   : ����
  ��    ��   : if
  ��������   : 2015��9��15��
  ����޸�   :
  ��������   : ������ǽ����д���ļ�����ļ�����
  �����б�   :
              filrewall_save_rule
              firewall_config
              firewall_read_rule_file
              firewall_save_all_rules
              firewall_get_passwd
              firewall_save_passwd
  �޸���ʷ   :
  1.��    ��   : 2015��9��15��
    ��    ��   : if
    �޸�����   : �����ļ�

******************************************************************************/
#include "common.h"
#include "route_firewall.h"

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define RULE_FILE    ".firewall_rule"
#define PASSWD_FILE  ".passwd"

/*****************************************************************************
 �� �� ��  : firewall_save_all_rules()
 ��������  : �ѷ���ǽ������������й��򱣴浽�ļ�
 �������  : rt       TYPE_Route ���ͽṹָ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
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
 �� �� ��  : filrewall_save_rule()
 ��������  : ���¼ӵķ���ǽ���򱣴浽�ļ�
 �������  : rule     Ҫ����Ĺ���
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
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
 �� �� ��  : firewall_read_rule_file()
 ��������  : ��������ǽ�����ļ�������
 �������  : file_name       �ļ���
 �� �� ֵ  : ����ָ���ļ����ݵ��ײ���ָ��
 �޸�����  : 2015��9��15��
*****************************************************************************/
static char *firewall_read_rule_file(const char *file_name)
{
	FILE *fp = NULL;
	char *buf = NULL;
	ulint file_length = 0;

	fp = fopen(file_name, "rb");
	if(fp == NULL){
		//printf("Cannot open the flie!\n");
		//Z�ļ������ڣ��򴴽���Ȼ�󷵻�
		fp = fopen(file_name, "wb");
		fclose(fp);
		return;
	}

	fseek(fp,0,SEEK_END);
	file_length = ftell(fp);
	buf = (char *)malloc(file_length); //��̬�����ڴ�

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
 �� �� ��  : firewall_config()
 ��������  : ��������ǽ�����ļ������ݣ��������˹�������
 �������  : rt       TYPE_Route ���ͽṹָ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
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
 �� �� ��  : firewall_get_passwd()
 ��������  : ���ļ���ȡ����ǽ������
 �������  : rt       TYPE_Route ���ͽṹָ��
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
*****************************************************************************/
void firewall_get_passwd(TYPE_Route *rt)
{
	FILE *fp = NULL;
	char str[PASSWD_LEN] = "";
	int i, len;

	fp = fopen(PASSWD_FILE, "rb");
	if(fp == NULL) {
		//�ļ������ڣ��򴴽���Ȼ���˳�
		fp = fopen(PASSWD_FILE, "wb");
		fclose(fp);
		return;
	}

	len = fread(str, 1, PASSWD_LEN, fp); //fread ����ʵ�ʶ��Ŀ���
	len--;
	str[len] = 0; // ȥ�� \n

	for(i=0; i<len; i++) {
		str[i] -= ENCRYPT_KEY;
	}

	strcpy(rt->passwd, str);

	fclose(fp);
}

/*****************************************************************************
 �� �� ��  : firewall_save_passwd()
 ��������  : ����ǽ��������ܺ󱣴浽�ļ�
 �������  : passwd       Ҫ���������
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
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
 �� �� ��  : getch()
 ��������  : ��ȡһ���ַ�
 �������  : NULL
 �� �� ֵ  : NULL
 �޸�����  : 2015��9��15��
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
 �� �� ��  : get_passwd()
 ��������  : ��ȡ����
 �������  : pwd      �����ȡ�����ָ��
 �� �� ֵ  : max_len  �������󳤶�
 �޸�����  : 2015��9��15��
*****************************************************************************/
void get_passwd(char passwd[], int max_len)
{
	char ch = 0, i = 0;
	char buf[PASSWD_LEN];

	while(i < max_len)
	{
		ch = getch();
		if(ch == 10){       // �س���
			passwd[i] = 0;
			break;
		}
		else if(ch ==127) { // �ظ��
			//i--;
			//if(i<0) i = 0;
			continue;
		}
		passwd[i++] = ch;
		putchar('*');
	}

	passwd[max_len] = 0;
}
