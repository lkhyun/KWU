#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//#define MAX_PROCESSES 8
#define MAX_PROCESSES 64

int main(void)
{
	FILE *f_write = fopen("temp.txt","w");
	for(int i = 0; i<MAX_PROCESSES*2; i++)
	{
		fprintf(f_write, "%d\n",i+1);
	}
	
	fclose(f_write);
	return 0;
}
