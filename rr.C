#include<stdio.h>
int main()
{
	int n,,total_time=0,i=0,p=0,completed[100]={0}, time_remaining[100], quanta;
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	printf("Enter burst time of each process : ");
	for(i=0;i<n;++i)
	{
		scanf("%d",&time_remaining[i]);
	}
	for(i=0;i<n;++i)
	{
		total_time+=time_remaining[i];
	}

	printf("\n ");

	for(i=0;i<quanta;++i)
		printf("-");
	printf("\n|");
	for(i=0;i<)

}