#include<stdio.h>
#include<stdlib.h>
int index(int arr[],int data,int size)
{
	int i;
	for(i=0;i<size;++i)
	{
		if(arr[i]==data)
			return i;
	}
}
int main()
{
	int *queue,*tqueue,count,i,j,m,ti,indexsmall;
	float *burst,*arrival,*priority,*fcfsstart,*sjfstart,tf,current,smallest,favgw=0,favgtat=0,savgw=0,savgtat=0;
	int *fq,*sjfq;
	printf("Enter the number of processes: ");
	scanf("%d",&count);
	burst=(float*)calloc(count,sizeof(float));
	arrival=(float*)calloc(count,sizeof(float));
	queue=(int*)calloc(count,sizeof(int));
	tqueue=(int*)calloc(count,sizeof(int));
	fcfsstart=(float*)calloc(count,sizeof(float));
	sjfstart=(float*)calloc(count,sizeof(float));
	sjfq=(int*)calloc(count,sizeof(int));
	
	for(i=0;i<count;++i)
	{
		queue[i]=i;
	}
	printf("Enter the respective burst times (in ms) : ");
	for(i=0;i<count;++i)
	{
		scanf("%f",&burst[i]);
	}
	printf("Enter the respective arrival times (in ms) : ");
	for(i=0;i<count;++i)
	{
		scanf("%f",&arrival[i]);
	}
	for(i=0;i<count;++i) //Sorting according to arrival time
	{
		for(j=i+1;j<count;++j)
		{
			if(arrival[j]<arrival[i])
			{
				tf=arrival[i];
				arrival[i]=arrival[j];
				arrival[j]=tf;

				tf=burst[i];
				burst[i]=burst[j];
				burst[j]=tf;

				ti=queue[i];
				queue[i]=queue[j];
				queue[j]=ti;
			}
		}
	}
	for(i=0;i<count;++i)
	{
		tqueue[i]=queue[i];
	}
	current=arrival[0];
	for(i=0;i<count;++i) //calculating start times for fcfs scheduling
	{
		if(current<arrival[i])
		{
			current=arrival[i];
		}
		fcfsstart[i]=current;
		favgw=favgw+current-arrival[i];
		favgtat=favgtat+current+burst[i]-arrival[i];
		current=current+burst[i];
	}
	favgw=favgw/count;
	favgtat=favgtat/count;
	current=arrival[0];
	i=0;
	j=0;
	while(i<count)//Creating SJF queue
	{
		while((j<count)&&(arrival[j]<=current))
			++j;
		for(m=0;m<j;++m)
		{
			if(tqueue[m]==-1)
				continue;
			else
			{
				smallest=burst[m];
				indexsmall=m;
				break;
			}
		}
		for(m=0;m<j;++m)
		{
			if(tqueue[m]==-1)
				continue;
			if(burst[m]<smallest)
			{
				smallest=burst[m];
				indexsmall=m;
			}
		}
		tqueue[indexsmall]=-1;
		sjfq[i]=queue[indexsmall];
		current=current+burst[indexsmall];
		i=i+1;
	}
	current=arrival[index(queue,sjfq[0],count)];
	for(i=0;i<count;++i) //calculating start times for SJF scheduling
	{
		if(current<arrival[index(queue,sjfq[i],count)])
		{
			current=arrival[index(queue,sjfq[i],count)];
		}
		sjfstart[i]=current;
		savgw=savgw+current-arrival[index(queue,sjfq[i],count)];
		savgtat=savgtat+current+burst[index(queue,sjfq[i],count)]-arrival[index(queue,sjfq[i],count)];
		current=current+burst[index(queue,sjfq[i],count)];
	}
	savgw=savgw/count;
	savgtat=savgtat/count;
	printf("FCFS Gantt Chart : \n ");
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
		printf("-");
	printf("\n");
	printf("|");
	j=0;
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
	{
		if(i==fcfsstart[j])
		{
			printf("%d",queue[j]+1);
			++j;
		}
		else if((j!=0)&&((i+1)==fcfsstart[j]))
			printf("|");
		else
			printf(" ");
	}
	printf("|\n ");
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
		printf("-");
	printf("\n");
	printf("Average waiting time in FCFS : %f ms\n",favgw);
	printf("Average turn-around time in FCFS : %f ms\n",favgtat);
	printf("SJF Gantt Chart : \n ");
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
		printf("-");
	printf("\n");
	printf("|");
	j=0;
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
	{
		if(i==sjfstart[j])
		{
			printf("%d",sjfq[j]+1);
			++j;
		}
		else if((j!=0)&&((i+1)==sjfstart[j]))
			printf("|");
		else
			printf(" ");
	}
	printf("|\n ");
	for(i=0;i<(fcfsstart[count-1]+burst[count-1]);++i)
		printf("-");
	printf("\n");
	printf("Average waiting time in SJF : %f ms\n",savgw);
	printf("Average turn-around time in SJF : %f ms\n",savgtat);
	free(burst);
	free(arrival);
	free(queue);
	free(fcfsstart);
	free(sjfstart);
	free(sjfq);
	return 0;	
}