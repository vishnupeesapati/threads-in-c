#include<stdio.h>

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
FILE *f;

void * count_1()
{
	printf("%c",fgetc(f));
	puts("thread 1 \n");


}

void *count_2()
{
	printf("%c",fgetc(f));
	 puts("thread 2 \n");

	
	
}



void main()
{
	f = fopen("lol.txt","r+");
	pthread_t t1,t2;
	pthread_create(&t1,NULL,(void *)&count_1,NULL);
	pthread_create(&t2,NULL,(void *)&count_2,NULL);

	pthread_join(t2,NULL);
	pthread_join(t1,NULL);
}

