#include <stdio.h>
#include <string.h>
#include "link.h"

void help()
{
	printf("-----------------------------------\n");
	printf("->help  : 帮助信息                  \n");
	printf("->insert: 插入一个新节点             \n");
	printf("->print : 遍历整个链表               \n");
	printf("->search: 查询某个节点               \n");
	printf("->delete: 查删除某个节点             \n");
	printf("->free  : 释放整个节点               \n");
	printf("->exit  : 退出                      \n");
	printf("-----------------------------------\n");
}

int main(int argc,char *argv[])
{
	char cmd[128] = "";
	STU *head = NULL;
	
	while(1)
	{
		scanf("%s",cmd);
		
		if(strcmp(cmd,"help")==0)
		{
			help();
		}
		else if(strcmp(cmd,"insert")==0)
		{
			STU temp;
			printf("please input the num,name,score:\n");
			scanf("%d %s %d",&temp.num,temp.name,&temp.score);
			head = insert_link(head, temp);
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
				printf("%d %s %d\n",ret->num,ret->name,ret->score);
			}
		}
		else if(strcmp(cmd,"delete")==0)
		{
			int num = 0;
			printf("Please input delete num\n");
			scanf("%d",&num);
			head = delete_link(head,num);	
		}
		else if(strcmp(cmd,"free")==0)
		{
			printf("-----free link-----\n");	
			head = free_link(head);
		}
		else if(strcmp(cmd,"exit")==0)
		{
			printf("----- exit -----\n");	
			head = free_link(head);
			break;
		}
	}
	return 0;
}
