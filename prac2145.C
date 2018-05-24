#include<stdio.h>

int main()
{
	int arr[100],frame[100],n,f,i,j,k,hit=0,found=-1,fault=1;
	int ref[100],lowest,l_idx=0,page_faults,temp;
	char bin[8];
	float hit_ratio;
	printf("Enter the number of frames : ");
	scanf("%d",&f);
	for(j=0;j<f;++j)
	{
		frame[j]=-1;
		ref[j]=0;
	}
	printf("Enter the number of page requests : ");
	scanf("%d", &n);
	printf("Enter the page numbers : ");
	for(i=0;i<n;++i)
	{
		scanf("%d",&arr[i]);
	}
	for(i=0;i<n;++i)
	{
		fault=1;
		printf("\n");
		found=-1;
		for(j=0;j<f;++j)
		{
			if((frame[j]==-1)&&(found==-1))
			{
				found=j;
				frame[j]=arr[i];
				ref[j]=ref[j]+128;
				break;

			}
			ref[j]=ref[j]/2;
			if(frame[j]==arr[i])
			{
				++hit;
				found=j;
				fault=0;
				ref[j]=ref[j]+128;
			}
		}
		if(found==-1)
		{
			lowest=ref[0];
			l_idx=0;
			for(j=1;j<f;++j)
			{
				if(ref[j]<lowest)
				{
					l_idx=j;
					lowest=ref[j];
				}
			}
			frame[l_idx]=arr[i];
			found=l_idx;
			ref[l_idx]=128;
		}
		
		for(j=0;j<f;++j)
		{
			if(frame[j]==-1)
			{
				printf("  ");
				continue;
			}
			printf("%d ",frame[j]);
			temp=ref[j];
			for(k=7;k>=0;--k)
			{
				if(temp%2)
					bin[k]='1';
				else
					bin[k]='0';
				temp=temp/2;
			}
			for(k=0;k<8;++k)
			{
				printf("%c",bin[k]);
			}
			printf("\n");
		}
		if(fault)
			{
				printf("Page fault occured. Replaced page at frame %d.\n",found);
			}
	}
	hit_ratio=(float)hit/n;
	page_faults=n-hit;
	printf("\nThe hit ratio is : %f",hit_ratio);
	printf("\nNumber of page faults : %d", page_faults);
	printf("\n");
	return 0;

}