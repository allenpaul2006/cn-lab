#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc,timer, frame;
	
	struct sockaddr_in serveraddr;
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
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(socketdesc,(struct sockaddr*)&serveraddr, sizeof(serveraddr))<0)
	{
			printf("cant connect\n");
			return -1;	
	}
	printf("Enter the no of frames");
	scanf("%d",&frame);
	while(frame > 0)
	{
		memset(servermsg,'\0',sizeof(servermsg));
		memset(clientmsg,'\0',sizeof(clientmsg));
		
		printf("frame msg");
		scanf("%s",clientmsg);
		
		int ack=0;
		while(!ack)
		{
			timer=10;
			send(socketdesc, clientmsg, strlen(clientmsg),0);
			while(timer > 0)
			{
				memset(servermsg,'\0',sizeof(servermsg));
				if(recv(socketdesc,servermsg,sizeof(servermsg),0)   <=0)
				{
					timer --;
					continue;
				}
				if(strcmp(servermsg, "n")==0)
				{
					printf("\n waiting ...\n");
					timer--;
				}
				else if ( strcmp(servermsg, "y")==0)
				{
					printf("\n server acknoledgement \n");
					ack=1;
					frame--;
					break;
				}
			}
			if(!ack)
			{
				printf("\n server not acknowledge, resending...\n ");
			}
		}
	}
	close(socketdesc);
	return 0;
}
	