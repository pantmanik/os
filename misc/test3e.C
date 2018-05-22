#include<stdio.h>
#include"misc/miniz.c"
int main()
{
FILE *FileIn = fopen("test3.gz", "rb");

//output file
FILE *FileOut = fopen("test3u.C", "wb");

//get the file size of the input file
fseek(FileIn, 0, SEEK_END);
unsigned long FileInSize = ftell(FileIn);

//buffers for the raw and uncompressed data
void *RawDataBuff = malloc(FileInSize);
void *UnCompDataBuff = NULL;

//read in the contents of the file into the source buffer
fseek(FileIn, 0, SEEK_SET);
fread(RawDataBuff, FileInSize, 1, FileIn);
//allocate a buffer big enough to hold the uncompressed data, we can cheat here
//because we know the file size of the original
uLongf UnCompSize = 482000;
UnCompDataBuff = malloc(UnCompSize);


//all data we require is ready so compress it into the source buffer, the exact
//size will be stored in UnCompSize
uncompress((Bytef*)UnCompDataBuff, &UnCompSize, (const Bytef*)RawDataBuff, FileInSize);

//write the decompressed data to disk
fwrite(UnCompDataBuff, UnCompSize, 1, FileOut);
return 0;
}