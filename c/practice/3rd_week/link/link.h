#ifndef __LINK_H__
#define __LINK_H__

typedef struct student
{
	int num;
	char name[64];
	int score;
	
	struct student *next;
}STU;

/*******************************************/
extern STU *insert_link(STU *head, STU temp);
extern void print_link(STU *head);
extern STU *search_link(STU *head, char *name);
extern STU *delete_link(STU *head, int num);
extern STU *free_link(STU *head);
#endif
