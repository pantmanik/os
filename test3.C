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
	printf("%d %d %d",sem[0],sem[1],sem[2]);
	shmdt(sem);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}