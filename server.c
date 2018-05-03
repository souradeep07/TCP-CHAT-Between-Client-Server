#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PENDING 5

int main()
{

	int sockserver;
	int sockclient;
	int recvMsgSize;
	char buff[64];
	char buffer[64];
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=PF_INET;
	serveraddr.sin_port=htons(9699);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if((sockserver=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("Error creating socket\n");
		exit(1);
	}else{ printf("Socket instance created\n"); }


	if(bind(sockserver,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0){
		printf("error binding.\n");
		exit(1);
	}else{ printf("binding success\n"); }
	if(listen(sockserver,PENDING)<0){
		printf("Error opening port for listening\n");
		exit(1);
	}else{ printf("Listening\n"); }

	unsigned int clientl=sizeof(clientaddr);
	
	
	if ((sockclient = accept(sockserver, (struct sockaddr *) &clientaddr,&clientl)) < 0){
		printf("Error accepting\n");
		exit(1);
	}
	else{
		printf("ACCEPTED\n");
	}
	
	while(1){

		if ((recvMsgSize = recv(sockclient, &buff, 64, 0)) < 0){
			printf("recv() failed\n") ;
			exit(1);
		}
		else{
			printf("RECEIVED\n");
			buff[recvMsgSize]='\0';
		}
		
		printf("Received from Client: %s\n",buff);
		
		printf("Enter text to send: ");
		scanf ("%[^\n]%*c", buffer);

		if (send(sockclient, &buffer, strlen(buffer), 0) != recvMsgSize)
			printf("send() failed\n");
		else
			printf("Sent successful\n");

		
	}
	close(sockclient);
	close(sockserver);
}
