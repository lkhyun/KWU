#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <time.h>
#include <assert.h>
#include <string.h>

uint8_t* Operation;
uint8_t* compiled_code;
int segment_id;

void sharedmem_init(); // 공유 메모리에 접근
void sharedmem_exit();
void drecompile_init(); // memory mapping 시작 
void drecompile_exit(); 
void* drecompile(uint8_t *func); //최적화하는 부분

int main(void)
{
    //FILE *file = fopen("50test.txt","a");
	int (*func)(int a);
	int i;

	struct timespec start, end;
	

	sharedmem_init();
	drecompile_init();

	func = (int (*)(int a))drecompile(Operation);//optimization
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("result: %d\n",func(1));//run function
    clock_gettime(CLOCK_MONOTONIC, &end);
	drecompile_exit();
	sharedmem_exit();

    printf("total execution time: %.6f\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
    //fprintf(file,"%.6f\n",(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
    //fclose(file);
	return 0;
}

void sharedmem_init() //get shared memory
{
	int size = PAGE_SIZE;
	segment_id = shmget(1234, size, 0);
	Operation = (uint8_t*)shmat(segment_id, NULL, 0);
}

void sharedmem_exit() //detach and remove shared memory
{
	shmdt(Operation);
	shmctl(segment_id, IPC_RMID, NULL);
}

void drecompile_init() //memory mapping
{
	compiled_code = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0); //read and write permission
    assert(compiled_code != MAP_FAILED);
}

void drecompile_exit()
{
	msync(compiled_code, PAGE_SIZE, MS_ASYNC); //memory synchronization
	munmap(compiled_code, PAGE_SIZE); //memory unmapping
}

void* drecompile(uint8_t* func)
{
    int a = 0;
#ifdef dynamic
	int i = 0,j = 0;
	int add_optimizor = 0;
    int sub_optimizor = 0;
    int imul_optimizor = 1;
    int div_optimizor = 1; 

    while(func[i] != 0xc3)
    {
        if (func[i] == 0x83 && func[i+1] == 0xc0) // add
        {
            while (func[i] == 0x83 && func[i + 1] == 0xc0)
            {
                add_optimizor += func[i + 2];
                i = i + 3;
            }
            compiled_code[j++] = 0x83;
            compiled_code[j++] = 0xc0;
            compiled_code[j++] = add_optimizor;
            add_optimizor = 0;
            continue;
        }
        else if(func[i] == 0x83 && func[i+1] == 0xe8)//sub
        {
            while (func[i] == 0x83 && func[i + 1] == 0xe8)
            {
                sub_optimizor += func[i + 2];
                i = i + 3;
            }
            compiled_code[j++] = 0x83;
            compiled_code[j++] = 0xe8;
            compiled_code[j++] = sub_optimizor;
            sub_optimizor = 0;
            continue;
        }
        else if(func[i] == 0x6b && func[i+1] == 0xc0)//imul
        {
            while (func[i] == 0x6b && func[i + 1] == 0xc0)
            {
                imul_optimizor *= func[i + 2];
                i = i + 3;
            }
            compiled_code[j++] = 0x6b;
            compiled_code[j++] = 0xc0;
            compiled_code[j++] = imul_optimizor;
            imul_optimizor = 1;
            continue;
        }
        else if(func[i] == 0xf6)//div
        {
            while (func[i] == 0xf6)
            {
                div_optimizor *= 2;
                i = i + 2;
            }
            compiled_code[j++] = 0xb2; //mov
            compiled_code[j++] = div_optimizor;
            compiled_code[j++] = 0xf6; //div
            compiled_code[j++] = 0xf2;
            compiled_code[j++] = 0xb2; //mov
            compiled_code[j++] = 0x02; //dl = 2
            div_optimizor = 1;
            continue;
        }
        else
        {
            compiled_code[j++] = func[i++];
        }
    }
    compiled_code[j] = 0xc3;
	while (compiled_code[a] != 0xc3) 
    {
		printf("%x ", compiled_code[a++]);
	}
	printf("%x ", compiled_code[a]);

	mprotect(compiled_code, PAGE_SIZE, PROT_READ | PROT_EXEC); //add read and execute permission
	return compiled_code;
#endif

    memcpy(compiled_code,func,PAGE_SIZE);
	a = 0;
	while (compiled_code[a] != 0xc3) 
    {
		printf("%x ", compiled_code[a++]);
	}
	printf("%x ", compiled_code[a]);

	mprotect(compiled_code, PAGE_SIZE, PROT_READ | PROT_EXEC); //add read and execute permission
	return compiled_code;
}


