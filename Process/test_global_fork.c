#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 全局变量 */
int g_value = 100;

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {   
        /* 父进程 */
        printf("parent value:%d\n", g_value);   
        g_value += 100;
        printf("parent g_value:%d, parent processId:%d\n", g_value, getpid());
    }
    else if (pid == 0)
    {
        /* 子进程 */
        usleep(300);
        printf("child g_value:%d, child processId:%d\n", g_value, getpid());
    }
    else if (pid < 0)
    {
        return -1;
    }


    while(1)
    {
        printf("while.....\n");
        sleep(3);
    }
}