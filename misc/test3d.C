#include <stdio.h>
#include "misc/miniz.c"
int main()
{
	FILE *fin=fopen("test3.C","rb");
	FILE *fout=fopen("test3.gz","wb");
	fseek(fin,0,SEEK_END);
	unsigned long finsize = ftell(fin);
	void *rawbuff=malloc(finsize);
	void *compbuff=NULL;
	uLongf compbuffsize = (uLongf)(finsize + (finsize * 0.1) + 12);
	compbuff=malloc((size_t)(compbuffsize));
	fseek(fin,0,SEEK_SET);
	fread(rawbuff,finsize,1,fin);
	uLongf destbuffsize;
	compress2((Bytef*)compbuff, (uLongf*)&destbuffsize,
          (const Bytef*)rawbuff, (uLongf)finsize, Z_BEST_COMPRESSION);
	fwrite(compbuff,destbuffsize,1,fout);
	return 0;


}