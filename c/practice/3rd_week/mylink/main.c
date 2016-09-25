#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "link.h"

#define MAX  6  //队列大小


char mygetch() 
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

void help()
{
	system("clear");
	printf("-----------------------------------\n");
	printf("->help  : 帮助信息                -\n");
	printf("->insert: 插入一个新节点          -\n");
	printf("->print : 遍历整个链表            -\n");
	printf("->search: 查询某个节点            -\n");
	printf("->delete: 查删除某个节点          -\n");
	printf("->free  : 释放整个节点            -\n");
	printf("->sort  : 将链表排序              -\n");
	printf("->invert: 倒置整个链表            -\n");
	printf("->exit  : 退出                    -\n");
	printf("-----------------------------------\n");
}

int main(int argc,char *argv[])
{
	char cmd[128] = "";
	int count = 0;
	STU *head = NULL;
	
	system("clear");
	help();
	while(1)
	{
		printf("cmd: ");
		fflush(stdout);
		scanf("%s",cmd);
		
		if(strcmp(cmd,"help")==0)
		{
			help();
		}
		else if(strcmp(cmd,"insert")==0)
		{
			int num;
			char ch, temp[48];
			STU new;
			
			while(1)
			{
				printf("please input the num, name, score: ");
				//scanf("%d %s %d",&new.num,new.name,&new.score);
				fscanf(stdin,"%d %s %d",&new.num,new.name,&new.score);
				gets(temp);

				if(new.num != num)
				{
					if(count < MAX)
					{
						head = insert_link(head, new);
						count++;
					}
					else
					{
						head = delete_head(head);
						head = insert_link(head, new);
					}
					num = new.num;
					if(head != NULL) //成功插入新节点
					{
						printf("按任意键继续，按‘Esc'结束\n");
						ch = mygetch();
					
						if(ch == 27)//Esc 键的ASCII 码为27
						{
							printf("结束插入！\n");
							break;
						} 
					}
				}
				else
				{
					printf("\n输入无效！\n");
				}
			}
		}
		else if(strcmp(cmd,"print")==0)
		{
			printf("-----print-----\n");
			print_link(head);		
		}
		else if(strcmp(cmd,"search")==0)
		{
			char name[64] = "";
			STU *ret;
			printf("please input search name\n");	
			scanf("%s",name);
			
			ret = search_link(head, name);
			
			if(ret == NULL)
			{
				printf("not found\n");
			}
			else
			{
				printf("num: %-4d name:%-8s score: %-3d\n",ret->num,ret->name,ret->score);
			}
		}
		else if(strcmp(cmd,"delete")==0)
		{
			int num = 0;
			printf("Please input delete num\n");
			scanf("%d",&num);
			head = delete_link(head,num);	
			count--;
			if(count < 0) count = 0;
		}
		else if(strcmp(cmd,"free")==0)
		{
			printf("-----free link-----\n");	
			head = free_link(head);
		}
		else if(strcmp(cmd,"sort")==0)
		{
			printf("-----sort link from score-----\n");	
			sort_link(head);
			print_link(head);
		}
		else if(strcmp(cmd,"invert")==0)
		{
			printf("-----invert link-----\n");	
			head = invert_link(head);
			print_link(head);
		}
		else if(strcmp(cmd,"exit")==0)
		{
			printf("----- exit -----\n");	

			if(head != NULL)
			{
				head = free_link(head);
			}
			break;
		}
		else
		{
			printf("命令不存在！需要帮助，请输入“help”\n");
		}
	}
	return 0;
}
