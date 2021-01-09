#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MY_FIFO_FILE "CS_FIFO" 			//CS_FIFO file is created

int main()
{
	int fs, exit, recv_bytes;
   	char recv_msg[80], sent_msg[80];

   	mkfifo(MY_FIFO_FILE, S_IFIFO|0640);
   	fs = open(MY_FIFO_FILE, O_RDWR);
   	
   	printf("SERVER: Chat Away!! To stop, send \"OK,BYE.\"\n\n");
   
   	while(1)
   	{
      		recv_bytes = read(fs, recv_msg, sizeof(recv_msg));
      		recv_msg[recv_bytes] = '\0';
      		printf("CLIENT SENT ME: \"%s\" \n", recv_msg);
      		exit = strcmp(recv_msg, "OK,BYE.");
      		
      		if (exit == 0)
      		{
         		close(fs);
         		break;
      		}
      		
      		printf("I AM SENDING BACK:");
      		fgets(sent_msg, sizeof(sent_msg), stdin);
      		sent_msg[strlen(sent_msg) - 1] = '\0';
      		write(fs, sent_msg, strlen(sent_msg));
      		sleep(2);
   	}
   	return 0;
}
