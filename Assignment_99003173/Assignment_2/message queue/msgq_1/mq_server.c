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
   	key_t K1;
   	int msg_ID;
   
   	K1 = ftok("SHRIRAM", 65);					//Unique key
   	msg_ID = msgget(K1, 0666 | IPC_CREAT);			//Message queue and return id
   
   	msgrcv(msg_ID, &M1, sizeof(M1), 1, 0); 			//Receive M1 from client
   	printf("Received Message is : %s \n", M1.msg);		//Display the M1 recieved

   	printf("Message sent to client: ");
   	fgets(M1.msg, 50, stdin);
   	msgsnd(msg_ID, &M1, sizeof(M1), 0);
   
   	return 0;
}
