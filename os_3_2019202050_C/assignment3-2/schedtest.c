#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/resource.h>

#define MAX_PROCESSES 10000

int main(void)
{
    struct timespec start,end;
    int policy[3] = {SCHED_OTHER,SCHED_FIFO,SCHED_RR};
    int priority[3] = {1,50,99};
    int nicearr[3] = {-20,0,19};
    for (int j = 0; j < 3; j++) //three policy
    {
        for (int k = 0; k < 3; k++) //three priority
        {
            clock_gettime(CLOCK_MONOTONIC, &start); //start time
            for (int i = 0; i < MAX_PROCESSES; i++)
            {
                if (!fork())
                {
                    struct sched_param param;
                    if(j == 0)
                    {
                        param.__sched_priority = 0;
                        sched_setscheduler(getpid(), policy[j], &param);
                        setpriority(PRIO_PROCESS,getpid(),nicearr[k]);
                    }
                    else
                    {
                        param.__sched_priority = priority[k];
                        sched_setscheduler(getpid(), policy[j], &param);
                    }
    
                    char filename[30];
                    char buf[10];
                    sprintf(filename, "./%s/%d", "temp", i + 1);
                    FILE *f_read = fopen(filename, "r");
                    fscanf(f_read, "%s", buf);
                    fclose(f_read);
                    exit(0);
                }
            }
            for (int i = 0; i < MAX_PROCESSES; i++)
            {
                wait(NULL);
            }
            clock_gettime(CLOCK_MONOTONIC, &end); //end time
            if(policy[j] == SCHED_OTHER){printf("Standard Round Robin Time Sharing(Nice:%d): ",nicearr[k]);}
            else if(policy[j] == SCHED_FIFO){printf("FIFO(Priority:%d): ",priority[k]);}
            else if(policy[j] == SCHED_RR){printf("Round Robin(Priority:%d): ",priority[k]);}
            printf("%.6f\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
        }
    }

    return 0;
}
