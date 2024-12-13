#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

//#define MAX_PROCESSES 8
#define MAX_PROCESSES 64
int number1[MAX_PROCESSES*2];
void* work(void* arg) //function called by thread
{
    int* i = (int*)arg;
    int *thread_result = (int*)malloc(sizeof(int));
    *thread_result = number1[*i]+number1[*i+1];
    
    pthread_exit((void*)thread_result);//return result
}
int main(void)
{
    pthread_t tid;
    int *result;
    struct timespec start,end;
    clock_gettime(CLOCK_MONOTONIC, &start);//start time
    FILE *f_read = fopen("temp.txt", "r");

    if (f_read == NULL)
    {
        perror("File open error");
        return 1;
    }
    for (int i = 0; i < MAX_PROCESSES * 2; i++)
    {
        fscanf(f_read, "%d", &number1[i]);
    }
    for (int j = MAX_PROCESSES*2; j > 1; j = j / 2) //loop log n
    {
        for (int i = 0; i < j; i = i + 2)
        {
            pthread_create(&tid,NULL,work,&i); //thread creation
            pthread_join(tid,(void**)&result); //thread wait
            number1[i/2] = *result;
            free(result);
        }
    }
    fclose(f_read);
    clock_gettime(CLOCK_MONOTONIC, &end); //end time
    printf("value of thread : %d\n",number1[0]);
    printf("%.6f\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);

    return 0;
}

