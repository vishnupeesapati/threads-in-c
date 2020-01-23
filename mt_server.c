#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<unistd.h>
#include<vlc/vlc.h>
#include<fcntl.h>
# define cl close(sock) 
int flag=0;
libvlc_instance_t *ins;
libvlc_media_player_t *player;
pthread_t prev;
void *acc()
{
puts("accelerating");
}
void *back()
{
puts("decelerating");

}
void *left()
{
puts("left");

}
void *right()
{
puts("right");

}
void *play_music(void *s)
{


flag=1;
/*
int sock = *(int *)s;
int fd=open("t.mp3",O_RDWR);
unsigned char song[10000000];
recv(sock,song,10000000,0);
write(fd,song,10000000);
close(fd);
*/
//printf("%d",libvlc_audio_get_track(player));
ins = libvlc_new(0,NULL);
libvlc_media_t *file;
//song initialization code
file  = libvlc_media_new_path(ins,"t.mp3");
player = libvlc_media_player_new_from_media(file);
libvlc_media_player_play(player);
while(flag);
libvlc_media_release(file);
libvlc_media_player_release(player);
libvlc_release(ins);
close(*(int *)s);
}

void *handle_music(void *s)
{
flag=!flag;
if(flag==0)
pthread_join(prev,NULL);
pthread_create(&prev,NULL,(void *)play_music,s);
}

void * handle(int *s)
{
pthread_t t;
int sock = *(int *)s;
//printf("%d is open",sock);
char *c = (char *)malloc(20);
recv(sock,c,20,0);
while(c++,*c!='$');
c++;
switch(*c)
{
case '1':
pthread_create(&t,NULL,(void *)acc,NULL);
pthread_detach(t);
cl;
break;
case '2':
pthread_create(&t,NULL,(void *)back,NULL);
pthread_detach(t);
cl;
break;
case '3':
pthread_create(&t,NULL,(void *)acc,NULL);
pthread_detach(t);
cl;
break;
case '4':
pthread_create(&t,NULL,(void *)left,NULL);
pthread_detach(t);
cl;
break;
case '5':
pthread_create(&t,NULL,(void *)right,NULL);
pthread_detach(t);
cl;
break;
case '6':
pthread_create(&t,NULL,(void *)handle_music,(void *)&sock);
pthread_detach(t);
break;
}

//free(c);
}

void main(int argc,char **argv)
{
pthread_t t[10];
int sock = socket(AF_INET,SOCK_STREAM,0);
printf("%d socket issued \n",sock);
struct sockaddr_in serv,client;
serv.sin_addr.s_addr = INADDR_ANY;
serv.sin_port = htons(atoi(argv[1]));
printf("%d",atoi(argv[1]));
serv.sin_family = AF_INET;
socklen_t s=sizeof(struct sockaddr);
int i=0;
if(!bind(sock,(struct sockaddr *)&serv,sizeof(serv)))
printf("socket bound to port %s",argv[1]);
if(!listen(sock,10000))
puts("listen successfull");

int sock_new  ;
while(1)
{
printf("\n");
sock_new = accept(sock,(struct sockaddr *)&client,&s);
if(sock_new)
{
printf("accepted");
pthread_create(t+i,NULL,(void *)handle,(void *)&sock_new);
pthread_detach(t[i]);
i++;
i%=10;
}
else
puts("client dropped");
}

}



