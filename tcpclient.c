#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc,clientsock,clientsize;
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
	printf("socet created\n");
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(8080);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(socketdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		printf("Error connecting");
		return -1;
		
	}
	printf("Done conencting\n");
	printf("Enter the message \n");
    gets(clientmsg);
	/*fgets(clientmsg, sizeof(clientmsg),stdin);
	clientmsg[strcspn(clientmsg,"\n")] = '\0';
	*/
	
	if(send(socketdesc,clientmsg, strlen(clientmsg),0) < 0)
	{
		printf("cant send");
		return -1;
	}
	
	if(recv(socketdesc,servermsg, sizeof(servermsg),0) < 0)
	{
		printf("cant recive message\n");
		return -1;
	}
	printf("mesage from server is %s ", servermsg);
	
	close(socketdesc);
	
	return 0;
}
	