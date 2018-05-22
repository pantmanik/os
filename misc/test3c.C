#include<stdio.h>
int main(int argc,char *argv[])
{
	int err=rename(argv[1],argv[2]);
	printf("%d",err);
	return 0;
}