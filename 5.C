#include<stdio.h>
#include<stdlib.h>
int main()
{
	float *rr_burst,*pri_burst,*pri_start,priavgw=0,priavgtat=0,tf,max_time=0;
	int *pri_q,*fcfs_q,*priority,count,i,j,ti,quanta,busy;
	printf("Enter the number of processes: ");
	scanf("%d",&count);
	printf("Enter the time quanta (in ms) : ");
	scanf("%d",&quanta);
	rr_burst=(float*)calloc(count,sizeof(float));
	pri_burst=(float*)calloc(count,sizeof(float));
	pri_q=(int*)calloc(count,sizeof(int));
	fcfs_q=(int*)calloc(count,sizeof(int));
	priority=(int*)calloc(count,sizeof(int));
	for(i=0;i<count;++i)
	{
		fcfs_q[i]=i;
		pri_q[i]=i;
	}
	printf("Enter the respective burst times (in ms) : ");
	for(i=0;i<count;++i)
	{
		scanf("%f",&rr_burst[i]);
		pri_burst[i]=rr_burst[i];
		max_time=max_time+rr_burst[i];
	}
	printf("Enter the respective priorities : ");
	for(i=0;i<count;++i)
	{
		scanf("%d",&priority[i]);
	}	
	for(i=0;i<count;++i) //Sorting according to priority
	{
		for(j=i+1;j<count;++j)
		{
			if(priority[j]>priority[i])
			{
				tf=pri_burst[i];
				pri_burst[i]=pri_burst[j];
				pri_burst[j]=tf;

				ti=pri_q[i];
				pri_q[i]=pri_q[j];
				pri_q[j]=ti;

				ti=priority[i];
				priority[i]=priority[j];
				priority[j]=ti;
			}
		}
	}
	busy=0;
	for(i=0;i<count;++i)
	{
		pri_start[i]=busy;
		priavgw=priavgw+busy;
		priavgtat=priavgtat+busy+pri_burst[i];
		busy+=pri_burst[i];
	}
	priavgw=priavgw/count;
	priavgtat=priavgtat/count;
	j=0;
	busy=0;
	printf("Priority Scheduling Gantt Chart : \n ");
	for(i=0;i<max_time;++i)
		printf("-");
	printf("\n");
	printf("|");
	for(i=0;i<max_time;++i)
	{
		if(i==busy)
		{
			printf("%d",pri_q[j]+1);
			busy=busy+pri_burst[j];
			++j;
		}

		else
			printf(" ");
	}
	printf("|\n ");
	for(i=0;i<max_time;++i)
		printf("-");
	printf("\n");
	printf("Average wait time in Priority Scheduling : %f ms\n",priavgw);
	printf("Average turn-around time in Priority Scheduling : %f ms\n",priavgtat);
	printf("Round-Robin Scheduling Gantt Chart : \n ");
	for(i=0;i<max_time;++i)
		printf("-");
	printf("\n");
	printf("|");
	j=0;
	ti=0;
	for(i=0;i<max_time;++i)
	{
		if(ti==0)
		{
			if (rr_burst[j]<=quanta)
			{
				printf("%d",fcfs_q[j]+1);
				rr_burst[j]=0;
				j=(j+1)%count;
				ti=0;
			}
			else
			{
				printf("%d",fcfs_q[j]+1);
				rr_burst[j]-=quanta;
				j=(j+1)%count;
				ti=(ti+1)%quanta;
			}
		}
		else
		{
			ti=(ti+1)%quanta;
			printf(" ");
		}

	}
	printf("|\n ");
	for(i=0;i<max_time;++i)
		printf("-");
	printf("\n");
	return 0;
}