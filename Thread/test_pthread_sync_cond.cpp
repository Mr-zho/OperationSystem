#include <iostream>
using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <queue>

/* 任务队列 */
queue<int> g_taskqueue;
#define QUEUE_SIZE 5

#define TOTAL_SNUM  20


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

/* 条件变量 : 任务队列里面有数据，就发这个条件变量 */
pthread_cond_t g_ptoc = PTHREAD_COND_INITIALIZER;
/* 条件变量 : 任务队列里面没有数据(空数据)，就发这个条件变量 */
pthread_cond_t g_ctop = PTHREAD_COND_INITIALIZER;

/* 状态码 */
typedef enum STATUS_CODE
{
    ON_SUCCESS,
    ON_FAIL
}STATUS_CODE;


void * thread_produce(void * arg)
{
    for (int idx = 1; idx <= (TOTAL_SNUM); idx++)
    {
        pthread_mutex_lock(&g_mutex_lock);
        #if 0
        /* 任务队列满了 */
        if (g_taskqueue.size() == QUEUE_SIZE)
        {   
            pthread_cond_wait(&g_ctop, &g_mutex_lock);
        }
        #else
        /* 任务队列满了 */
        while (g_taskqueue.size() == QUEUE_SIZE)
        {   
            pthread_cond_wait(&g_ctop, &g_mutex_lock);
        }
        #endif
        g_taskqueue.push(idx);
        printf("produce idx:%d\n", idx);
        pthread_mutex_unlock(&g_mutex_lock);
        pthread_cond_signal(&g_ptoc);
    }

    pthread_exit(NULL);
}

void * thread_consume(void * arg)
{
    for (int idx = 0; idx < TOTAL_SNUM; idx++)
    {
        pthread_mutex_lock(&g_mutex_lock);
        /* 任务队列是空的, 没有数据 */
        #if 0
        if (g_taskqueue.size() == 0)
        {
            pthread_cond_wait(&g_ptoc, &g_mutex_lock);
        }
        #else
        while (g_taskqueue.size() == 0)
        {
            pthread_cond_wait(&g_ptoc, &g_mutex_lock);
        }
        #endif
        int taskNode = g_taskqueue.front();
        g_taskqueue.pop();
        pthread_mutex_unlock(&g_mutex_lock);
        pthread_cond_signal(&g_ctop);
        printf("thread id is :%ld, consume idx:%d\n", pthread_self(), taskNode);
    }
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

#if 0
    for (int idx = 1; idx <= QUEUE_SIZE; idx++)
    {
        g_taskqueue.push(idx);
    }
    printf("g_taskqueue.size:%ld\n", g_taskqueue.size());

    
    while (g_taskqueue.size())
    {
        int taskNode = g_taskqueue.front();
        g_taskqueue.pop();
        printf("tasknode is %d\n", taskNode);
    }

    int a = 24;
    int b = a >> 1;
    printf ("b:%d\n", b);
#endif

#if 1 
    pthread_t produce_threadId;
    pthread_t consume_threadId1,  consume_threadId2;

    /* 创建生产者线程 */
    int ret = pthread_create(&produce_threadId, NULL, thread_produce, NULL);
    if (ret != 0)
    {
        perror("pthread_create error\n");
        exit(0);
    }

    /* 创建消费者线程1 */
    ret = pthread_create(&consume_threadId1, NULL, thread_consume, NULL);
    if (ret != 0)
    {
        perror("pthread_create error\n");
        exit(0);
    }
    /* 创建消费者线程2 */
    ret = pthread_create(&consume_threadId2, NULL, thread_consume, NULL);
    if (ret != 0)
    {
        perror("pthread_create error\n");
        exit(0);
    }

    pthread_join(produce_threadId, NULL);
    pthread_join(consume_threadId1, NULL);
    pthread_join(consume_threadId2, NULL);

    printf("g_sharedresource:%d\n",  g_sharedresource);
#endif
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













