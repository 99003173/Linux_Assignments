#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

#define MAXSIZE 10       
int stack[MAXSIZE];     
int top = -1;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;		//Implemented using a mutex lock m1
sem_t s1;							// and semaphore s1

int empty()							//To check if stack is empty
{
   	if(top == -1)
      		return 1;
   	else
      		return 0;
}

int full()							//To check if stack is full
{	
   	if(top == MAXSIZE)
      		return 1;
   	else
      		return 0;
}

int at_top()							//To check value at top of stack
{
   	return stack[top];
}

int pop()							//To pop value from stack
{
   	int value;
   	if(!empty())
   	{
      		value = stack[top];
      		top = top - 1;
      		return value;
   	}
   	else
   	{
      		printf("Stack is empty!\n");
   	}
}

int push(int value)						//To push value into stack
{
   	if(!full())
   	{
      		top = top + 1;   
      		stack[top] = value;
   	}
   	else
   	{
      		printf("Stack is full!\n");
   	}
}

void* push_thread(void* p)					//Producer Thread
{
	printf("Pushing first\n");
	pthread_mutex_lock(&m1);
	push(10);
	push(20);
	push(30);
	push(40);
	pthread_mutex_unlock(&m1);
	printf("Pushing Completed\n");
	sem_post(&s1);
}

void* pop_thread(void* p)					//Consumer Thread
{
	sem_wait(&s1);
	printf("Poping atlast\n");
	pthread_mutex_lock(&m1);
	pop();
	pop();
	printf("Poping Completed\n");
	pthread_mutex_unlock(&m1);
}

int main()
{
	pthread_t t1,t2;
	sem_init(&s1,0,0);
	pthread_create(&t1,NULL,push_thread,NULL);
	pthread_create(&t2,NULL,pop_thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	if(!empty())
		printf("Top Element at %d is %d\n", top, at_top());
	pthread_mutex_destroy(&m1);
	sem_destroy(&s1);
	return 0;
}
