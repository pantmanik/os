#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/wait.h>
int main()
{
	int shmid;
	int *sem;
	key_t key = 12345;
	shmid=shmget(key, sizeof(int)*3, 0666|IPC_CREAT);
	sem=(int *)shmat(shmid,0,0);
	sem[0]=1;
	sem[1]=2;
	sem[2]=3;
	// if(fork==0)
	// {
	// 	printf("%d %d %d",sem[0],sem[1],sem[2]);
	// }
	// else
	// {
	// 	printf("%d %d %d",sem[0],sem[1],sem[2]);
	// 	scanf("%d",&sem[0]);
	// 	scanf("%d",&sem[1]);
	// 	scanf("%d",&sem[2]);
	// 	wait(NULL);
	// }
	pause();
	shmdt(sem);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}