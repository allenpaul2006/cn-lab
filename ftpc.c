//ftpCLIENT.C
#include<stdio.h>
#include<sys/types.h>
//#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
//#include<netdb.h>
#include<stdlib.h>
int main()
{
	int socketdesc,n,length;
	struct sockaddr_in serveraddr;
	char filename[20],filedata[300];
	socketdesc=socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=2000;
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(socketdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
	{
		printf("\nError:Cannot connect...");
		exit(0);
	}
	printf("Enter the name of the file : ");
	scanf("%s",filename);
	length=strlen(filename);
	write(socketdesc,filename,length);
	n=read(socketdesc,filedata,300);
	printf("\nThe contents of the file: \n\n");
	printf("%s",filedata);
	close(socketdesc);
}