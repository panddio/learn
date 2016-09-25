/*************************************************************************
	> File Name: DieWithMessage.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 May 2016 03:52:24 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void DieWithUserMessage(const char *msg, const char *detail) {
  fputs(msg, stderr);
  fputs(": ", stderr);
  fputs(detail, stderr);
  fputc('\n', stderr);
  exit(1);
}

void DieWithSystemMessage(const char *msg) {
  perror(msg);
  exit(1);
}
