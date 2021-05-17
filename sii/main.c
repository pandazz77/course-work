#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include "env_handler.h"

SOCKET MakeSocket(char *ip_source,int wPort){
	SOCKET sock = (SOCKET)NULL;
	SOCKADDR_IN Addr = {0};
	
	sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	
	if( sock == INVALID_SOCKET ){
		printf("invalid socket\n");
		return (SOCKET)NULL;
	}


	Addr.sin_family = AF_INET;
	Addr.sin_port = htons( wPort);
	Addr.sin_addr.s_addr = inet_addr(ip_source);

	if( bind( sock,(SOCKADDR *)&Addr, sizeof(Addr) ) == SOCKET_ERROR ){
		printf("Error in bind socket\n");
		closesocket(sock);
		return (SOCKET)NULL;
	}
	
	return sock;
}

int SendData( SOCKET sock, char *ip_target, int wDstPort,char message[]){
	SOCKADDR_IN SendAddr = {0};
	
	SendAddr.sin_family = AF_INET;
	SendAddr.sin_port = htons( wDstPort);
	SendAddr.sin_addr.s_addr = inet_addr(ip_target);
		
	sendto( sock, message, strlen(message),0,(SOCKADDR *)&SendAddr,sizeof(SendAddr));
	
	return 1;
}

int inputf(void *p){
	printf("Enter message: ");
	char buf[1024];
	int r;
	fgets(buf,sizeof(buf),stdin);
	r = sscanf(buf,"%s",p);
	return !r;
}

int main( int argc, char ** argv){	
	WSADATA wsaData = {0};
	SOCKET sock;

	char ip_target[32];
	char ip_source[32];

	int wDstPort;
	int wSrcPort;
	
	get_env_data(&ip_target,&wDstPort,&ip_source,&wSrcPort);

	WSAStartup( MAKEWORD(2,2), &wsaData);
	sock = MakeSocket(ip_source, wSrcPort);
	if(sock){
		while(1){
			char message[1024];
			inputf(&message);
			SendData(sock,ip_target,wDstPort,message);	
		}
	}
	
	return 0;
}
