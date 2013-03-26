/* 一个简单的聊天室代码 */

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

int sockfd;

int creat_socket()
{
	//1.create socket
	sockfd = socket(AF_INET, SOCK_DGRAM,0);
	
	//2.bind port
	struct sockaddr_in staddr;
	staddr.sin_family = AF_INET;
	staddr.sin_port = htons(9000);
	staddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd,(struct sockaddr*)&staddr,sizeof(staddr));
	
	//3.set broadcast
	int on = 1;	
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	
	return 0;

}

int recvdata()
{	
	char buf[4096];
	int len;
	struct sockaddr_in staddr;
	
	while(1){
		memset(buf,0,4096);
		recvfrom(sockfd,buf,4096,0,(struct sockaddr*)&staddr,&len);
		printf("from:%16s : %s\n",inet_ntoa(staddr.sin_addr),buf);
	}
}


void *senddata(void *arg)
{
	struct sockaddr_in staddr;
	char buf[4096];
	int len = sizeof(staddr);

	staddr.sin_family = AF_INET;
	staddr.sin_port = htons(9000);
	staddr.sin_addr.s_addr = inet_addr("192.168.104.255");

	while(1){
		fgets(buf,4096,stdin);
		sendto(sockfd,buf,strlen(buf)-1,0,(struct sockaddr*)&staddr,len);
	}
}


int main()
{
	pthread_t tid;
	creat_socket();
	
	pthread_create(&tid,NULL,senddata,NULL);

	recvdata();
	
}
