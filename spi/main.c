#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include "env_handler.h"

SOCKET MakeSocket(char *ip_source,int wPort)
{
	//printf("port: %d\n",wPort);
	SOCKET sock = (SOCKET)NULL;
	SOCKADDR_IN Addr = {0};
	
	sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	
	if( sock == INVALID_SOCKET )
	{
		printf("invalid socket\n");
		return (SOCKET)NULL;
	}


	Addr.sin_family = AF_INET;
	Addr.sin_port = htons( wPort);
	Addr.sin_addr.s_addr = inet_addr(ip_source);

	if( bind( sock,(SOCKADDR *)&Addr, sizeof(Addr) ) == SOCKET_ERROR )
	{
		printf("Error in bind socket\n");
		closesocket( sock);
		return (SOCKET)NULL;
	}
	
	return sock;
}

int EmulateThread(SOCKET sock)
{
	SOCKADDR_IN RecvAddr = {0};
	int iRet, iRecvSize;
	char buf[1024];
	
	printf("thread started\n");
	while(1)
	{
		iRecvSize = sizeof(RecvAddr);
		iRet = recvfrom( sock, buf, 1024, 0, (SOCKADDR *)&RecvAddr, &iRecvSize );
		if( iRet == SOCKET_ERROR ){
			printf("socket error\n");
			continue;
		}
			
		buf[iRet] = '\0';
		printf( "[%s:%d] : %s\n", inet_ntoa( RecvAddr.sin_addr), htons( RecvAddr.sin_port),buf);
	}
	
	return 0;
}



int main( int argc, char ** argv)
{
	WSADATA wsaData = {0};
	SOCKET sock;
	
	char ip_target[32];
	char ip_source[32];

	int wDstPort;
	int wSrcPort;
	

	get_env_data(&ip_target,&wDstPort,&ip_source,&wSrcPort);
	
	/*
	if( argc != 3)
	{
		printf( "Usage : udpchar [srcport] [dstport]\n");
		return -1;
	}
	
	wSrcPort = atoi(argv[1]);
	wDstPort = atoi(argv[2]);
	*/
	
	WSAStartup( MAKEWORD(2,2), &wsaData);
	sock = MakeSocket(ip_source, wSrcPort);
	
	
	EmulateThread(sock);
	
	WSACleanup();
	
	return 0;
}
