#include "server.h"
#include "message.h"


///
unsigned int SocketUsed = 0;								//使用中的套接字个数

SOCKET_SCB s_scb[SOCKET_MAX_NUM];							//套接字块
pthread_mutex_t mutex;										//线程互斥锁
//



void mutext_init(pthread_mutex_t *mutex)
{
	pthread_mutex_init(mutex,NULL);
}

void SocketSCBInit(void)
{
	int j;
	for(j = 0;j < SOCKET_MAX_NUM; j++)
	{
		s_scb[j].socket_id = -1;
		memset(&s_scb[j].client_info,0,sizeof(struct sockaddr_in));
	}
}

int server_init(char *ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	int bindnum;
	if(sock < 0)
	{
		return sock;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	bindnum = bind(sock,(struct sockaddr *)&local,sizeof(local));
	if(bindnum < 0)
	{
		printf("bind fail\n");
		return bindnum;
	}

	if(listen(sock,SOCKET_MAX_NUM) < 0)
	{
		printf("listen fail\n");
		return -1;
	}
	else
	{
		printf("listen ing ....\n");
	}
	return sock;

}

int main()
{
	int SocketNbr = 0;
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	
	SocketSCBInit();
	mutext_init(&mutex);

	int listen_sock = server_init("0.0.0.0",8888);

	if(listen_sock < 0)
	{
		printf("server init fail\n");
		return 0;
	}
	
	thread_message_create();
	while(1)
	{
		//检查是否还有可用套接字
		for(SocketNbr = 0;SocketNbr < SOCKET_MAX_NUM; SocketNbr++)
		{
			if(s_scb[SocketNbr].socket_id < 0)
			{
				break;
			}
		}

		if(SocketNbr < SOCKET_MAX_NUM)
		{
			s_scb[SocketNbr].socket_id = accept(listen_sock,(struct sockaddr*)&client,&len);
			if(s_scb[SocketNbr].socket_id < 0)
			{
				printf("accept error\n");
				s_scb[SocketNbr].socket_id = -1;
				memset(&s_scb[SocketNbr].client_info,0,sizeof(struct sockaddr_in));
			}
			else
			{
				connect_in(SocketNbr,&client);
			}
		}
		else
		{
			//printf("socket connected FULL\n");
		}

	}

}

void *thread_socket(void *arg)
{

	int SocketNbr = arg;
	int socket_id = s_scb[SocketNbr].socket_id;
	int recv_len;
	unsigned char buf[256] = {0};
	
	while(1)
	{
		recv_len = recv(socket_id,buf,sizeof(buf),0);

		if(recv_len <= 0)
		{
			break;
		}

		buf[recv_len] = '\0';
		send(socket_id,buf,recv_len,0);
		
		printf("read info from %d : \n%s\n",socket_id,buf);
	}

	connect_out(SocketNbr,socket_id);
	
}

void connect_in(int SocketNbr,struct sockaddr* client)
{
	pthread_t id;

	pthread_mutex_lock(&mutex);
	SocketUsed++;
	memcpy(&s_scb[SocketNbr].client_info,client,sizeof(struct sockaddr));
	pthread_mutex_unlock(&mutex);

	printf("new dev join -> %d %s\n",s_scb[SocketNbr].socket_id,inet_ntoa(s_scb[SocketNbr].client_info.sin_addr));
	printf("avillable socket_id :%d\n",SOCKET_MAX_NUM - SocketUsed);
	pthread_create(&id,NULL,thread_socket,(void *)SocketNbr);
	pthread_detach(id);
}

void connect_out(int SocketNbr,int socket_id)
{
	printf("dev quit -> %d %s\n",s_scb[SocketNbr].socket_id,inet_ntoa(s_scb[SocketNbr].client_info.sin_addr));
	pthread_mutex_lock(&mutex);
	s_scb[SocketNbr].socket_id = -1;
	memset(&s_scb[SocketNbr].client_info,0,sizeof(struct sockaddr_in));
	SocketUsed--;
	pthread_mutex_unlock(&mutex);

	printf("avillable socket_id :%d\n",SOCKET_MAX_NUM - SocketUsed);
	close(socket_id);
}

