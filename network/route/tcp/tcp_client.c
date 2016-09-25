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
	char ch;
	char i = 0;
	
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

int tcp_receive_msg(int sockfd, char recv[])
{
	int len = 0;

	while(1) {
		len = recv(sockfd, recv, sizeof(recv), 0);
		if((strcmp(recv, "#end#") == 0) || (len == 0)){
			return len;
		}

		printf("%s", recv);
	}
}

void tcp_send_cmd(char cmd[], int sockfd)
{
	int len  = 0;
	char recv[1024] = "";	
	
	if(strcmp(cmd, "help") == 0){
		send(sockfd, cmd, strlen(cmd), 0);	
		tcp_receive_msg(sockfd, recv);					
	}
	else if(strcmp(cmd,"arp") == 0){
		send(sockfd, cmd, strlen(cmd), 0);
		tcp_receive_msg(sockfd, recv);
	}
	else if(strcmp(cmd,"ifconfig") == 0){
		send(sockfd, cmd, strlen(cmd), 0);
		tcp_receive_msg(sockfd, recv);
	}
	else if(strcmp(cmd,"lsfire") == 0){	
		send(sockfd, cmd, strlen(cmd), 0);
		tcp_receive_msg(sockfd, recv);		
	}
	else if(strcmp(cmd,"setfire") == 0){
		
		int i;
		char passwd[PASSWD_LEN] = "";
		
		send(sockfd, cmd, strlen(cmd), 0);		
		for(i=0; i<2; i++) {		
			tcp_receive_msg(sockfd, recv);
			
			get_passwd(passwd, PASSWD_LEN-1);
			send(sockfd, passwd, strlen(passwd), 0);
	
			tcp_receive_msg(sockfd, recv);	
			if(strcmp(recv, "passed") == 0) break;		
		}
		
		if(i == 2) return;
		
		tcp_receive_msg(sockfd, recv);	
	
		while(1) {			
			bzero(cmd, RULE_LEN);

			tcp_receive_msg(sockfd, recv);
							
			fgets(cmd, RULE_LEN, stdin);	
			len = strlen(cmd);
			rule[len-1] = 0; //ȥ�� \n	
			
			if(strcmp(cmd,"ls") == 0){
				send(sockfd, cmd, strlen(cmd), 0);
				tcp_receive_msg(sockfd, recv);
			}
			else if(strcmp(cmd,"-h") == 0) {
				send(sockfd, cmd, strlen(cmd), 0);
				tcp_receive_msg(sockfd, recv);			
			}	
			else if(strncmp(cmd,"-d",2) == 0) {
				char *prule = NULL;
				prule = cmd+3; //���� "-d "
				send(sockfd, cmd, strlen(cmd), 0);
			}
			else if(strcmp(cmd,"passwd") == 0) {
				send(sockfd, cmd, strlen(cmd), 0);
				tcp_receive_msg(sockfd, recv);								
				get_passwd(passwd, PASSWD_LEN-1);
				send(sockfd, passwd, strlen(passwd), 0);				
			}
			else if(strcmp(cmd,"esc") == 0){
				send(sockfd, cmd, strlen(cmd), 0);
				tcp_receive_msg(sockfd, recv);	
				break;
			}
			else {			
				send(sockfd, cmd, strlen(cmd), 0);
			}
		}		
	}	

	out:
	pthread_mutex_unlock(&rt->mutex);// ����
}
