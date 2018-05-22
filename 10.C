#include<stdio.h>
int main()
{
 int n,m[20],i,j,sb[20],b[20][20],x;
 printf("Enter the total number of files:");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {       printf("Enter starting block of file %d:",i+1);
          scanf("%d",&sb[i]);
          printf("Enter number of blocks occupied by file %d:",i+1);
          scanf("%d",&m[i]);
          printf("Enter blocks occupied by file %d:",i+1);
          for(j=0;j<m[i];j++)
                   scanf("%d",&b[i][j]);
 } printf("\nFile\t index\tlength\n");
 for(i=0;i<n;i++)
 {
          printf("%d\t%d\t%d\n",i+1,sb[i],m[i]);
 }printf("\nEnter file name:");
 scanf("%d",&x);
 printf("File name is: %d\n",x);
 i=x-1;
 printf("Index is: %d\n",sb[i]);
 printf("Blocks occupied are:");
 for(j=0;j<m[i];j++)
          printf("%3d",b[i][j]);
printf("\n");
 return 0;
}