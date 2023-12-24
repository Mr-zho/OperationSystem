#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

/* 互斥锁和条件变量 */

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

/* 共享资源 */
int g_sharedresource = 10;

/* 锁静态初始化 */
pthread_mutex_t g_mutex_lock = PTHREAD_MUTEX_INITIALIZER;

/* 条件变量 */
pthread_cond_t g_ptoc;

/* 状态码 */
typedef enum STATUS_CODE
{
    ON_SUCCESS,
    ON_FAIL
}STATUS_CODE;


void * thread_func1(void * arg)
{
    /* 线程回收方式2: 线程分离 */
    // pthread_detach(pthread_self());
    int value = *(int *)arg;
    printf("thread_func1 value:%d, before g_sharedresource:%d\n", value, g_sharedresource);
    
    /*  futex */
    while(1)
    {
        sleep(1);
        
        pthread_mutex_lock(&g_mutex_lock);
        pthread_cond_wait(&g_ptoc, &g_mutex_lock);
        if (g_sharedresource >  0)
        {
            g_sharedresource--;
        }
        /* */
        pthread_mutex_unlock(&g_mutex_lock);
        pthread_cond_signal(&g_ptoc);
        // pthread_cond_signal(&g_ptoc);

        if (g_sharedresource <= 0)
        {
            break;
        }
    }
    #if 0
    while (g_sharedresource > 0 && !(pthread_mutex_lock(&g_mutex_lock)))
    {
        
        sleep(1);
        g_sharedresource--;
        pthread_mutex_unlock(&g_mutex_lock);
    }
    #endif
    // printf("g_sharedresource:%d\n", value, g_sharedresource);
    pthread_exit(NULL);
}

void * thread_func2(void * arg)
{
    /* 线程回收方式2: 线程分离 */
    // pthread_detach(pthread_self());
    // pthread_mutex_lock(&g_mutex_lock);

    while(1)
    {
        usleep(300);
        pthread_mutex_lock(&g_mutex_lock);
        pthread_cond_wait(&g_ptoc, &g_mutex_lock);
        if (g_sharedresource >  0)
        {
            g_sharedresource--;     
        }
        pthread_mutex_unlock(&g_mutex_lock);
        pthread_cond_signal(&g_ptoc);

        if (g_sharedresource <= 0)
        {
            break;
        }
    }
    #if 0
    while (g_sharedresource > 0 && !(pthread_mutex_lock(&g_mutex_lock)))
    {
        usleep(300);
        g_sharedresource--;
        pthread_mutex_unlock(&g_mutex_lock);
    }
    #endif
    // printf("thread_func2 value:%ld, g_sharedresource:%d\n", pthread_self(), g_sharedresource);
    pthread_exit(NULL);
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

    /* 动态初始化锁资源, 调用init函数 */
#if 0
    pthread_mutex_t mutex_lock;
    pthread_mutex_init(&mutex_lock, NULL);
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

    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);
    printf("g_sharedresource:%d\n", g_sharedresource);

    // while(1);
    /* 资源回收 */
    // 方式1:
#if 0
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













