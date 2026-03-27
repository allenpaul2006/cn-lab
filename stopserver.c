#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc,clientsock, clientsize;
	struct sockaddr_in serveraddr,clientaddr;
	char servermsg[2000],clientmsg[2000];
	
	memset(servermsg,'\0',sizeof(servermsg));
	memset(clientmsg,'\0',sizeof(clientmsg));
	
	socketdesc = socket(AF_INET,SOCK_STREAM,0);
	if (socketdesc<0)
	{
		return -1;
		printf("Error creating socket");
		
	}
	printf("socet created");
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(8080);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(socketdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		printf("Error in binding process");
		return -1;
		
	}
	printf("Done Binding");
	if(listen(socketdesc,1) < 0)
	{
		printf("Error listening \n");
		return -1;
	}
	printf("\nlistening to incoming conenctions\n");
	
	clientsize=sizeof(clientaddr);
	clientsock=accept(socketdesc,(struct sockaddr*)&clientaddr,&clientsize);
	
	if(clientsock < 0)
	{
		printf("\ncant cononect\n");
		return -1;
		
	}
	printf("\nClient connected at ip : %s and port %i \n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	
	while(1)
	{
		memset(clientmsg,'\0', sizeof(clientmsg));
		int recvstatus=recv(clientsock,clientmsg,sizeof(clientmsg),0);
		if (recvstatus <=0)
		{
			printf("client disconnected");
			break;
		}
		printf("\n message from client : %s \n", clientmsg);
	while(1)
	{
		memset(servermsg,'\0', sizeof(servermsg));
		printf("\n send ack (y) or nack(n) : ");
		scanf("%s",servermsg);
		send(clientsock, servermsg, strlen(servermsg),0);
		
		if(strcmp(servermsg,"y") == 0 )
		{
			break;
		}
		printf( "\n nack sent...\n");
	}
	}
	
	close(clientsock);
	close(socketdesc);
	return 0;
}
