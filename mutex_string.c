#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

int counter = 0;

char **c ;



pthread_mutex_t lock;


void * print()
{
	puts("just before lock level");
	printf("%d \n",counter);
	pthread_mutex_lock(&lock);

	switch(counter)
	{
		case 0:
			puts("entered 0");
			counter = 1;
			strcpy(c[0],"lol");
			//puts(c[0]);
			break;
		case 1:
			puts("entered 2");
			counter=2;
			strcpy(c[1],"pizza");
			puts(c[0]);
			break;
		case 2:
			puts("enter 3 and finish");
                        strcpy(c[2],"party");
			puts(c[1]);
			break;
	}

	pthread_mutex_unlock(&lock);
}






void main()
{
	c  = (char **)malloc(3*sizeof(char *));
	c[0] = (char *)malloc(10*sizeof(char));
	c[1] = (char *)malloc(10*sizeof(char));
	c[2] = (char *)malloc(10*sizeof(char));



if(pthread_mutex_init(&lock,NULL)==0)
	puts("lock initialized");
pthread_t t[3];
for(int i=0;i<=2;i++)
{
	pthread_create(&t[i],NULL,(void *)&print,NULL);
	
}

	pthread_join(t[0],NULL);
	pthread_join(t[1],NULL);
	   pthread_join(t[2],NULL);


pthread_mutex_destroy(&lock);

}
