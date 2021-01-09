#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
   long type;
   char msg[100];
}M1;

int main()
{
   	key_t k1;
   	int msg_ID;
   	
   	k1 = ftok("SHRIRAM", 65); 					//Unique key
   	msg_ID = msgget(k1, 0666 | IPC_CREAT); 			//Message queue and return id
   	M1.type = 1;
   	
   	printf("Enter Command: ");
   	fgets(M1.msg, 100, stdin);

   	msgsnd(msg_ID, &M1, sizeof(M1), 0); 				//Send command
   	msgrcv(msg_ID, &M1, sizeof(M1), 1, 0); 
   	return 0;
}
