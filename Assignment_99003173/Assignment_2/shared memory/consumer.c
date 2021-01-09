#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h> 						

int main()
{
    const char *name = "shared_memory";
    const char *SEM1= "fill";
    const char *SEM2= "avail";
    const char *SEM3= "mutex";
    int shm_fd; 
    int * shelf;
    int loop=6;
    sem_t * fill, * avail, * mutex;
    
    shm_fd = shm_open(name, O_RDWR, 0666);
    shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    fill = sem_open(SEM1, O_CREAT,0666,0);
    avail = sem_open(SEM2, O_CREAT, 0666, 3);
    mutex = sem_open(SEM3,O_CREAT,0666,1);
    while(loop--)
    {
        sem_wait(fill);
        sleep(rand()%2+1);
        sem_wait(mutex);
        (* shelf)--;
        sem_post(mutex);
        printf("Consumer: Using Resource %d left\n",*shelf);
        sem_post(avail);
    }

    sem_close(fill);
    sem_close(avail);
    sem_close(mutex);
    sem_unlink(SEM1);
    sem_unlink(SEM2);
    sem_unlink(SEM3);

    munmap(shelf, sizeof(int));
    close(shm_fd);
    shm_unlink(name);
    return 0;
}
