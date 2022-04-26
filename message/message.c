#include "message.h"
#include "menu.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

char sendbuf[200];


void *check_input(void *arg)
{
    printf("Successfully entered command input mode.\n");
    while(1)
    {
	//printf("%s","\033[1H\033[2J");    
        printf("Please enter '\033[;34mcommand\033[0m' or enter '\033[;34mhelp\033[0m' to get command help.\n");
        scanf("%s",sendbuf);
        if (strcmp(sendbuf,"quit") == 0)
        {
            break;
        }
        else if (strcmp(sendbuf,"help") == 0)
        {
           mess_help_show(); 
        }
	else if (strcmp(sendbuf,"menu") == 0)
        {
        	 pthread_t id;
       		 if (pthread_create(&id,NULL,thread_menu,NULL))
       		 {
               		 printf("error creating thread.\n");
       		 }
       		 pthread_join(id,NULL);
	}

        printf("input date:%s\n",sendbuf);
    }

}

void thread_message_create(void)
{
    pthread_t id;
    pthread_create(&id,NULL,check_input,NULL);
    pthread_detach(id);
}

//输出帮助信息
void mess_help_show(void)
{
    printf("%s","\033[1H\033[2J");	
    printf("'\033[;34mhelp\033[0m': List all instructions and how to use them.\n");
    printf("'\033[;34mquit\033[0m': Exit command input mode.\n");
    printf("'send': Send message externally.\n");
    printf("'\033[;34mmenu\033[0m': start menu.\n");
}
