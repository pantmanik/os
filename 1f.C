#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
	int fdO,fdC;
	fdO=open("1ftest.txt", O_RDONLY|O_CREAT);
	if(fdO!=-1)
		printf("File opened successfully\n");
	fdC=close(fdO);
	if(fdC==-1)
		printf("Error in closing file\n");
	else
		printf("File closed successfully\n");
	return 0;

}