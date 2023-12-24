#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOTAL_NUM   100
#define BUF_NUM     10

/* 进程 */
int main(int argc, const char *argv[])
{
    #if 0
    int array[100];//1-100
    int num[10];//num 1-10
    int n=10;
    for(int i=0;i<101;i++)
    {
        srand(i);
        array[100]=rand()%10+1;
        num[array(i)-1] = ++
    }
    for(int i=1;i<(n+1);i++)
    {

        num[10]
    }
    #endif

    #if 0
    srand(time(NULL));
    int array[TOTAL_NUM];//1-100
    memset(array, 0, sizeof(array)); 

    int nums[BUF_NUM];//num 1-10
    memset(nums, 0, sizeof(nums)); 


    int n=10;
    for(int idx = 0; idx < TOTAL_NUM; idx++)
    {
        /* [1 - 10] */
        array[idx]=rand() % 10 + 1;
    }

    int value = 0, num_index = 0;
    for(int idx = 0; idx < TOTAL_NUM; idx++)
    {
        value = array[idx];
        num_index = value - 1;
        nums[num_index]++;
    }
    
    int maxValue = 0;
    int suoyin = 0;
    for (int idx = 0; idx < BUF_NUM; idx++)
    {
        if (nums[idx] > maxValue)
        {
            maxValue = nums[idx];
            suoyin = idx;
        }
    }
    printf("value:%d,  fence:%d\n", suoyin + 1, maxValue);
    #endif
    int value = 66;
    
    int pipefd[2];
    memset(pipefd, 0, sizeof(pipefd));
    int ret = pipe(pipefd);
    if (ret == -1)
    {
        return -1;
    }
    
    pid_t pid = fork();
    if (pid > 0)
    {   
        /* 父进程 */
        #if 0
        printf("parent value:%d\n", value);
        value += 100;
        printf("parent value:%d, parent processId:%d\n", value, getpid());
        #else
        /* 关闭读的句柄 */
        close(pipefd[0]);
        value += 100;
        /* 父进程负责写 */
        write(pipefd[1], (void *)&value, sizeof(int));

        #if 0
        int readValue = 0;
        read(pipefd[0], &readValue, sizeof(int));
        printf("parent readValue:%d\n", readValue);
        #endif
        #endif  
    }
    else if (pid == 0)
    {
        #if 0
        /* 子进程 */
        printf("child value:%d, child processId:%d\n", value, getpid());
        sleep(30);
        exit(2);
        #else
        /* 子进程负责读 */
        /* 关闭写句柄 */
        close(pipefd[1]);

        usleep(300);
        int readValue = 0;
        read(pipefd[0], &readValue, sizeof(int));
        printf("child readValue:%d\n", readValue);
#if 0
        /* 管道只能读取一次 */
        int readValueAgain = 0;
        read(pipefd[0], &readValueAgain, sizeof(int));
        printf("child readValue:%d\n",readValueAgain);
#endif
        exit(2);
        #endif
    }
    else if (pid < 0)
    {
        return -1;
    }

#if 0
    int localvalue = 0;
    pid_t tmppid = wait(&localvalue);
    localvalue = WEXITSTATUS(localvalue);
    printf("tmppid:%d, localvalue:%d\n", tmppid, localvalue);
#endif
    while(1)
    {
        printf("while.....\n");
        sleep(3);
    }
    return 0;
}

