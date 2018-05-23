#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd,datai;
	char data[128];
	fd=open("helper1", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	scanf("%d",&datai);
	sprintf(data,"%d",datai);
	printf("%s",data);
	write(fd,data,strlen(data));
	close(fd);
	return 0;
}