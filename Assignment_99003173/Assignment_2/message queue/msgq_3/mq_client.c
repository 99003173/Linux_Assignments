#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

struct message
{
   long type;
   char msg[100];
   struct stat STAT;
}M1;

void read_file_attribute(struct stat STAT)
{
    struct tm DT;

    printf("\nFile access: ");
    if (STAT.st_mode & R_OK)
        printf("read ");
    if (STAT.st_mode & W_OK)
        printf("write ");
    if (STAT.st_mode & X_OK)
        printf("execute");

    printf("\nSize of the file: %ld", STAT.st_size);

    DT = *(gmtime(&STAT.st_ctime));
    printf("\nDate & time created: %d-%d-%d %d:%d:%d", DT.tm_mday, DT.tm_mon, DT.tm_year + 1900, 
                                              DT.tm_hour, DT.tm_min, DT.tm_sec);

    DT = *(gmtime(&STAT.st_mtime));
    printf("\nDate & time modified: %d-%d-%d %d:%d:%d \n", DT.tm_mday, DT.tm_mon, DT.tm_year + 1900, 
                                              DT.tm_hour, DT.tm_min, DT.tm_sec);

}

int main()
{
   key_t my_key;
   int msg_id;
   
   my_key = ftok("progfile", 65); 					//Unique key
   msg_id = msgget(my_key, 0666 | IPC_CREAT); 			//Message queue and return id
   M1.type = 1;
   
   printf("Enter File path: ");
   fgets(M1.msg, 100, stdin);
   
   msgsnd(msg_id, &M1, sizeof(M1), 0); 				//Send command
   msgrcv(msg_id, &M1, sizeof(M1), 1, 0); 
   read_file_attribute(M1.STAT);
   return 0;
}
