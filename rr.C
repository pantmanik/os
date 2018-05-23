#include<stdio.h>
int main()
{
	int n,current_time=0,total_time=0,test_time=0,i=0,j=0,quanta;
	int time_remaining[100],end_time[100],burst_time[100];
	float avg_waiting_time=0,avg_turnaround_time=0;
	printf("Enter the time quanta : ");
	scanf("%d",&quanta);
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	printf("Enter burst time of each process : ");
	for(i=0;i<n;++i)
	{
		scanf("%d",&burst_time[i]);
		time_remaining[i]=burst_time[i];
	}
	for(i=0;i<n;++i)
	{
		total_time+=time_remaining[i];
	}

	printf("\n ");
	current_time=0;
	for(i=0;i<total_time;++i)
		printf("-");
	printf("\n|");
	for(i=0;i<n;i=(i+1)%n)
	{
		if(current_time>=total_time)
			break;
		if(time_remaining[i]<=0)
			continue;
		
		printf("%d",i+1);
		if(time_remaining[i]<=quanta)
		{
			for(j=1;j<time_remaining[i];++j)
				printf(" ");
			current_time=current_time+time_remaining[i];
			time_remaining[i]=0;
			end_time[i]=current_time;
		}
		else
		{
			for(j=1;j<quanta;++j)
				printf(" ");
			current_time+=quanta;
			time_remaining[i]-=quanta;
		}
	}
	printf("|\n ");
	for(i=0;i<total_time;++i)
		printf("-");
	printf("\n");
	for(i=0;i<n;++i)
	{
		avg_turnaround_time+=end_time[i];
		avg_waiting_time+=end_time[i]-burst_time[i];
	}
	avg_waiting_time=avg_waiting_time/n;
	avg_turnaround_time=avg_turnaround_time/n;
	printf("The average waiting time is : %fms\n",avg_waiting_time);
	printf("The average turnaround time is : %fms\n",avg_turnaround_time);
	return 0;	

}