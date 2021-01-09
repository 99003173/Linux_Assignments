#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<unistd.h>
#include <sys/wait.h>

struct message
{
   long type;
   char msg[100];
}M1;

int main() 
{
   	key_t k1;
   	int msg_ID;
   	int c,s,ret;
   	
   	k1 = ftok("SHRIRAM", 65); 					//Unique key
   	msg_ID = msgget(k1, 0666 | IPC_CREAT); 			//Message queue and return id
   	
   	msgrcv(msg_ID, &M1, sizeof(M1), 1, 0); 			//Recieve Command
   	printf("Received Command is : %s \n", M1.msg);
   	
   	c=fork();
   	if(c==0)
   	{
   		s=execl("/bin/sh","sh","-c",M1.msg,NULL);
   	}
   	else
   	{
    		waitpid(c, &ret, 0); 
   		return 0;
   	}
}
