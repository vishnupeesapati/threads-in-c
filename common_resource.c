#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>

char *lol = "lol";

void* print()
{
	puts(lol);
}


void* print1()
{
	strcpy(lol,"pizza");
	puts(lol);
}

int main()
{

	pthread_t t1,t2;
	pthread_create(&t1,NULL,(void *)(& print),NULL);
	pthread_create(&t2,NULL,(void *)(& print1),NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

}
