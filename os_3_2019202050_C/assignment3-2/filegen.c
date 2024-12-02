#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_PROCESSES 10000

int main(void)
{
	mkdir("temp", 0777);
	for(int i = 0; i<MAX_PROCESSES; i++)
	{
		char filename[30];
		sprintf(filename,"./%s/%d","temp",i+1);
		FILE *f_write = fopen(filename,"w");
		fprintf(f_write, "%d",1+rand()%9);
		fclose(f_write);
	}
	return 0;
}
