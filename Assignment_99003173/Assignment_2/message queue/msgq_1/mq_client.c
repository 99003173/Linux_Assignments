#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
   long type;
   char msg[50];
}M1;

int main()
{
	key_t k1;
   	int msg_ID;
   	
   	k1 = ftok("SHRIRAM", 65); 					//Unique key
   	msg_ID = msgget(k1, 0666 | IPC_CREAT); 			//Message queue and return id
   	M1.type = 1;
   	printf("Message sent to server: ");
   	fgets(M1.msg, 50, stdin);
   	
   	msgsnd(msg_ID, &M1, sizeof(M1), 0); 				//Send M1 to server
   	msgrcv(msg_ID, &M1, sizeof(M1), 1, 0); 			//Receive M1 from server
   	
   	printf("Received Message is : %s \n", M1.msg);		//Display the M1 recieved

   	return 0;
}
