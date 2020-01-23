#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>

#include<pthread.h>
# define port 1112

void *com1()
{
	struct sockaddr_in client,target;
	socklen_t size = sizeof(struct sockaddr_in);
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(port);
	client.sin_family  = AF_UNIX;
	int sock = socket(AF_UNIX,SOCK_STREAM,0);
	if(bind(sock,(struct sockaddr*)&client,sizeof(client))== 0)
		puts("binded to port");
	listen(sock,5);
	if((sock = accept(sock,(struct sockaddr *)&target,&size)) > 0)
		puts("connection established");
	send(sock,"lol",4,0);
}

void *com2()
{
	 struct sockaddr_in client;
	 socklen_t size = sizeof(struct sockaddr_in);
	 client.sin_addr.s_addr = INADDR_ANY;
	 client.sin_port = htons(port);
	 client.sin_family  = AF_UNIX;
	 int sock = socket(AF_UNIX,SOCK_STREAM,0);
	 if(connect(sock,(struct sockaddr*)&client,sizeof(struct sockaddr))==0)
		 puts("connected");
	 char buf[4];
	 recv(sock,buf,4,0);
	 puts(buf);

}


void main()
{
	pthread_t t,t1;
	pthread_create(&t,NULL,(void *)&com1,NULL);
	pthread_create(&t1,NULL,(void *)&com2,NULL);
	pthread_join(t,NULL);
	pthread_join(t1,NULL);
}
