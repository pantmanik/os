#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	
	int fd;
	char data[80];
	if (!strcmp(argv[1],"r"))
	{
		fd=open(argv[2],O_RDONLY);
		printf("file opened in read mode\n");
	}
	else
	{
		fd=open(argv[2],O_WRONLY|O_CREAT);
	}
	if(fd==-1)
	{
		printf("Unable to open file\n");
		exit(-1);
	}
	if(!strcmp(argv[1],"r"))
	{
		while(read(fd,data,79)>0)
		{
			printf("%s",data);
		}
	}
	else
	{
		printf("Enter the content to be written on the file\n");
		scanf("%[^\n]%*c",data);
		strcat(data,"\0");
		write(fd,data,strlen(data));
	}
	printf("\n");
	close(fd);
	return 0;
}