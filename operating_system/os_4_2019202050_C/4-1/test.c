#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int a;
int b = 200;
int main()
{
	int c;
	int d;
	int *e = malloc(sizeof(int)*10);
	syscall(336, getpid()); 
	free(e);
	return 0;

}
