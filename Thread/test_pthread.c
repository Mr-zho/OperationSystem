#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

/* 结构体 的字节对齐是什么？ */
typedef struct stu_info
{
    int height;
    char sex;
#if 0
    int weight;
    char name[20];
    char address[20];
#endif
} stu_info;


#if 0
int printStuInfo(stu_info *newinfo, const stu_info *info)     /* 值传递 */
{
    printf("func size %ld\n", sizeof(info));

    // info->weight = 110;
}
#endif

/* 全局变量 */
int g_retval = 5;
/* 状态码 */
typedef enum STATUS_CODE
{
    ON_SUCCESS,
    ON_FAIL
}STATUS_CODE;

void * thread_func1(void * arg)
{
    int value = *(int *)arg;
    printf("thread_func1 value:%d\n", value);
    pthread_exit(NULL);
}

void * thread_func2(void * arg)
{
    pthread_t tid = *(pthread_t *)arg;
    printf("thread_func2 value:%ld, %ld\n", tid, pthread_self());
    /* 线程回收方式2: 线程分离 */
    pthread_detach(pthread_self());

    sleep(3);
    printf("thread_func2....\n");
    pthread_exit(&g_retval);
}

/* 命令行参数 */
int main(int argc, const char * argv[])
{
#if 0
    /* 字节对齐 */
    stu_info info;
    printf("size str_info:%ld\n", sizeof(info));
    info.weight = 120;

    printf("weight:%d\n", info.weight);
    printStuInfo(&info);

    printf("weight:%d\n", info.weight);
#endif
    int value = 666;
    pthread_t threadId1, threadId2 = 666;
    int ret = pthread_create(&threadId1, NULL, thread_func1, (void *)&value);
    if (ret != 0)
    {
        perror("pthread_create error\n");
        exit(0);
    }

    ret = pthread_create(&threadId2, NULL, thread_func2, (void *)&threadId2);
    if (ret != 0)
    {
        perror("pthread_create error\n");
        exit(0);
    }
    printf("threadId2:%ld\n", threadId2);


    sleep(2);
    /* 资源回收 */
    // 方式1:
#if 1
    int *retVal1 = NULL;
    pthread_join(threadId1, NULL);
    // printf("retVal1:%d\n", *retVal1);

    int dummynum = 10;
    int *retVal2 = &dummynum;
    pthread_join(threadId2, (void **)&retVal2);
    printf("dummynum:%d\n", *(retVal2));
#endif


    return 0;
}