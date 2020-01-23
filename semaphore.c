#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>
#include<string.h>


char * lol = "pizza";

void * test(void * arg)
{
puts(lol);
puts("from test \n");
pthread_exit( (pthread_t) *arg);
}


void * test_1()
{
	strcpy(lol,"lol");
	puts("from test 1 \n");
}


void main()
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,(void *)&test,(void *)t1);
	sleep(2);
	pthread_create(&t2,NULL,(void *)&test_1,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

}
