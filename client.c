#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sock;
	char buffer[64];
	char buff[64];
	int bytesreceived=0;
	struct sockaddr_in clientaddr;
	
	memset(&clientaddr,0,sizeof(clientaddr));
	clientaddr.sin_family=PF_INET;
	clientaddr.sin_port=htons(9699);
	clientaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("Error creating socket Instance\n");
		exit(1);
	}else{
		printf("Instance of socket created successfully\n");
	}	

	if(connect(sock,(struct sockaddr *)&clientaddr,sizeof(clientaddr))<0){
		printf("Connection failed\n");
		exit(1);
	}else{
		printf("Connected to Server\n");
	}
	
	while(1){
	
	printf("Enter text to send: ");
	scanf ("%[^\n]%*c", buffer);
	
	int string = strlen(buffer);

	if(send(sock,&buffer,string,0)!=string){
		printf("ERROR SENDING\n");
		exit(1);
	}else{
		printf("Sent\n");
	}
	
	if((bytesreceived=recv(sock,&buff,63,0))<=0){
			printf("Error receiving\n");
			exit(1);
		}else{
			printf("Bytes Received:%d\n",bytesreceived);
		}
		
		printf("Received from Server: %s\n",buff);
	
	}
}
