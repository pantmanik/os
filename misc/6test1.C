#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>  /* Needed for the wait function */
#include <unistd.h>    /* needed for the fork function */
#include <string.h>    /* needed for the strcat function */
#define SHMSIZE 27
int main() {
   int shmid;
   int *shm;

   if(fork() == 0) {
      shmid = shmget(2009, 5*sizeof(int), 0);
      shm = (int*)shmat(shmid, 0, 0);
      int *s=(int*)shm;  /* Set first location to string terminator, for later append */
      int i;
      for(i=0; i<5; i++) {  /* Variable to get the number into */
         printf("Enter number<%i>: ", i);
         scanf("%d", s);
         s=s+sizeof(int); /* Append number to string */
      }  /* Append newline */
      printf ("Child wrote ");
      for(i=0;i<5;++i)
      {
         printf("%d ",shm[i]);
      }
      shmdt(shm);
   }
   else {
      /* Variable s removed, it wasn't used */
      /* Removed first call to wait as it held up parent process */
      shmid = shmget(2009, SHMSIZE, 0777 | IPC_CREAT);
      shm = (int *)shmat(shmid, 0, 0);
      wait(NULL);
      int i;
      printf ("Parent reads ") ;
      for(i=0;i<5;++i)
      {
         printf("%d ",shm[i]);
      }
      shmdt(shm);
      shmctl(shmid, IPC_RMID, NULL);
   }
   return 0;
}