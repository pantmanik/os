#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
void wait(int *s)
{
    while(*s<=0);
    *s=*s-1;
}
void signal(int *s)
{
    *s=*s+1;
}
int main()
{
	int shmid_chopstick,shmid_loop,shmid_counter,i,pid;
	int *chopstick,*loop,*counter;
	char choice;
	key_t key_chopstick = 12345,key_loop = 12346,key_counter=12347;

	shmid_chopstick=shmget(key_chopstick, sizeof(int)*5, 0666|IPC_CREAT);
	shmid_loop=shmget(key_loop, sizeof(int), 0666|IPC_CREAT);
	
	
	chopstick=(int *)shmat(shmid_chopstick,0,0);
	loop=(int *)shmat(shmid_loop,0,0);
	

	*loop=1;
	for(i=0;i<5;++i)
		chopstick[i]=1;
	
	printf("Enter Index of philosopher (starts from 0) : ");
	again:
	scanf("%d",&pid);
	if(pid>=5)
	{
		printf("philosophers' index can't exceed 4, enter again : ");
		goto again;
	}
	printf("This is philosopher %d.\n",pid);
	printf("Enter e to eat and anything else to exit : \n");
	while(*loop)
	{
		scanf(" %c",&choice);
		if(choice=='e')
		{
			wait(&chopstick[pid]);
			wait(&chopstick[(pid+1)%5]);
			printf("Philosopher %d is eating. Enter t to think,anything else to exit : ",pid);
			scanf(" %c", &choice);
			signal(&chopstick[pid]);
			signal(&chopstick[pid+1]);
			if(choice=='t')
			{
				printf("Philosopher %d is thinking. Enter e to eat, anything else to exit : ",pid);
				continue;
			}
			else
			{
				*loop=0;
				break;
			}
		}
		else
		{
			*loop=0;
			break;
		}
	}

	shmdt(chopstick);
	shmctl(shmid_chopstick, IPC_RMID, 0);
	shmdt(loop);
	shmctl(shmid_loop, IPC_RMID, 0);
	return 0;
}