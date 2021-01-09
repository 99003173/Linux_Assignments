#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

# define MAX 10

int arr[MAX];
int front = -1;
int rear  = -1;

sem_t s1,s2;								//Implemented using 2 semaphores

void insert(int value)							//Function to insert value into circular queue
{
	if((front == 0 && rear == MAX-1) || (front == rear+1))
	{
		printf("Queue Overflow\n");
		return;
	}
	if (front == -1)
	{
		front = 0;
		rear = 0;
	}
	else
	{
		if(rear == MAX-1)
			rear = 0;
		else
			rear = rear+1;
	}
	arr[rear] = value ;
}

void delete()								//Function to delete from circular queue
{
	if (front == -1)
	{
		printf("Queue Underflow\n");
		return;
	}
	printf("Element deleted from queue is : %d\n", arr[front]);
	if(front == rear)
	{
		front = -1;
		rear=-1;
	}
	else
	{	
		if(front == MAX-1)
			front = 0;
		else
			front = front+1;
	}
}

void display()								//Function to display the whole circular queue
{
	int front_orig_pos = front,rear_orig_pos = rear;
	if(front == -1)
	{
		printf("Queue is empty\n");
		return;
	}
	printf("Circular Queue elements are :\n");
	if( front_orig_pos <= rear_orig_pos )
	{
		while(front_orig_pos <= rear_orig_pos)
		{
			printf("%d at position %d\n",arr[front_orig_pos],front_orig_pos);
			front_orig_pos++;
		}
	}
	else
	{
		while(front_orig_pos <= MAX-1)
		{
			printf("%d at position %d\n",arr[front_orig_pos],front_orig_pos);
			front_orig_pos++;
		}
		front_orig_pos = 0;
		while(front_orig_pos <= rear_orig_pos )
		{
			printf("%d at position %d\n",arr[front_orig_pos],front_orig_pos);
			front_orig_pos++;
		}
	}
	printf("\n");
}

void* insert_thread(void* p)						//Producer Thread
{
	sem_wait(&s2);
	printf("Inserting into circular queue\n");
	insert(10);
	insert(20);
	insert(30);
	insert(40);
	insert(50);
	sem_post(&s2);
	printf("Insertion finished\n");
	sem_post(&s1);
}

void* delete_thread(void* p)						//Consumer Thread
{
	sem_wait(&s1);	
	sem_wait(&s2);
	printf("Deleting from circular queue\n");
	delete();
	delete();
	delete();
	sem_post(&s2);
	printf("Delete operation finished\n");
}

int main()
{
	pthread_t t1,t2;
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	pthread_create(&t1,NULL,insert_thread,NULL);
	pthread_create(&t2,NULL,delete_thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	display();
	sem_destroy(&s1);
	sem_destroy(&s2);
	return 0;
}


