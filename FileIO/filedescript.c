#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#define BUFFER_SIZE 32

int main()
{
#if 0
    /* 当文件不存在的时候 没有O_CREAT参数 会打开文件失败. */
    int fd1 = open("./hello.txt", O_RDWR);
    printf("fd1:%d\n", fd1);

    close(fd1);
#endif

    #if 0
    /* 当文件不存在的时候 没有O_CREAT参数 会打开文件失败. */
    /* 但是不赋予mode权限. */
    int fd1 = open("./hello.txt", O_RDWR | O_CREAT);
    printf("fd1:%d\n", fd1);
    close(fd1);
    #endif

    #if 0
    /* 当文件不存在的时候 没有O_CREAT参数 会打开文件失败. */
    /* 赋予mode正常的权限. */
    int fd1 = open("./hello.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd1);
    close(fd1);
    #endif


    #if 0
    int fd1 = open("./hello1.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd1);

    int fd2 = open("./hello2.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd2);

    int fd3 = open("./hello3.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd3);

    int fd4 = open("./hello4.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd4);

    /* 关闭文件描述符 */
    close(fd1);
    
    /* 重新获取最小的文件描述符 */
    int fd5 = open("./hello5.txt", O_RDWR | O_CREAT, 0644);
    printf("fd1:%d\n", fd5);

    /* 关闭文件描述符 */
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);
    #endif


    #if 0
    /* 写磁盘文件 */
    int fd = open("./hello5.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        return -1;
    }
    char *buf = "hello world\n";
    write(fd, buf, strlen(buf) + 1);
    write(fd, buf, strlen(buf) + 1);
    write(fd, buf, strlen(buf) + 1);
    close(fd);
    #endif



    #if 0
    /* 读磁盘文件 */
    int fd = open("./hello5.txt", O_RDWR);
    if (fd == -1)
    {
        return -1;
    }
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));

    read(fd, buf, sizeof(buf) - 1);
    
    printf("buf:%s", buf);
    close(fd);
    #endif


    #if 0
    /* 读磁盘文件 & 文件指针 */
    int fd = open("./hello5.txt", O_RDWR);
    if (fd == -1)
    {
        return -1;
    }
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));

    read(fd, buf, 2);
    printf("buf:%s\n", buf);

    /* 类似于FILE中的库函数 */
    off_t offset = lseek(fd, 0, SEEK_CUR);
    printf("offset:%ld\n", offset);

    /* 覆盖文件指针后面位置的元素*/
    write(fd, "nicenice", strlen("nicenice"));

    /* 获取文件大小 */
    offset = lseek(fd, 0, SEEK_END);
    printf("offset:%ld\n", offset);

    close(fd);
    #endif
    

    return 0;
}