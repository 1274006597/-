#ifndef __SERVER_H
#define __SERVER_H

#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define SOCKET_MAX_NUM 				5000

typedef struct{
	int socket_id;
	struct sockaddr_in client_info;
}SOCKET_SCB;						//套接字块


void *thread_socket(void *arg);								//线程函数
void connect_in(int SocketNbr,struct sockaddr* client);		//连入
void connect_out(int SocketNbr,int socket_id);				//连出


#endif

