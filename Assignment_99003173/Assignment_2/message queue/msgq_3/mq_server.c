#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

struct message
{
   long type;
   char msg[100];
   struct stat STAT;
}M1;

int main()
{
   struct stat stats;
   key_t k1;
   int msg_ID,i,j;
   char file_path[100];
   
   k1 = ftok("SHRIRAM", 65); 					//Unique key
   msg_ID = msgget(k1, 0666 | IPC_CREAT); 			//Message queue and return id
   
   msgrcv(msg_ID, &M1, sizeof(M1), 1, 0); 			//Send command

   for(i=0;i<strlen(M1.msg);i++)
   {
   	if(M1.msg[i]==39||M1.msg[i]=='\n')
   	{}
   	else
   	{
   		file_path[j]=M1.msg[i];
   		j++;
   	}

    	if (stat(file_path, &M1.STAT) == 0)
    	{
        	msgsnd(msg_ID, &M1, sizeof(M1), 0);
    	}
    	else
    	{
        	printf("Unable to get file properties.\n");
        	printf("Please check whether '%s' file exists.\n", file_path);
    	}
    }
    return 0;
}

