#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc,clientsock,clientsize;//clientsize is not int it is socklen_t
	struct sockaddr_in serveraddr,clientaddr;
	char servermsg[2000],clientmsg[2000];
	
	memset(servermsg,'\0',sizeof(servermsg));
	memset(clientmsg,'\0',sizeof(clientmsg));
	
	socketdesc = socket(AF_INET,SOCK_STREAM,0);
	if (socketdesc<0)
	{
		printf("Error creating socket");
        return -1;
		
		
	}
	printf("socket created successfully\n");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(8080);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(socketdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		printf("Error in bingding process");
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
	printf("\nClient connected at ip \n");
	
	if(recv(clientsock,clientmsg, sizeof(clientmsg),0) < 0)
	{
		printf("cant recive message\n");
		return -1;
	}
	//printf("received message from IP:%s and port %i\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	printf("mesage from client is %s \n ", clientmsg);
	
    //strcpy(servermsg,"This is the server's message.");
    printf("enter msg\t");
   // gets(servermsg);
	fgets(servermsg, sizeof(servermsg), stdin);
	servermsg[strcspn(servermsg,"\n")]='\0';
    

	if(send(clientsock,servermsg,strlen(servermsg),0) < 0)
	{


		printf("Cant send");
		return -1;
	}
	close(clientsock);
	close(socketdesc);
	
	return 0;
}