// 使用系统调用。
#include <iostream>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>


// 故意搞一个不能一次读完的数组。
#define MAX_SIZE 10


int main()
{
    const char *filePath = "hello.txt";
    const char *writeStr = "He\nllo, software weekly.";


    int fd = open(filePath, O_RDWR | O_CREAT | O_TRUNC, 0755);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    write(fd, writeStr, strlen(writeStr));

    close(fd);


    int fd2 = open(filePath, O_RDONLY);
    if (-1 == fd2)
    {
        perror("open");


        return -1;
    }


    char readStr[MAX_SIZE] = {0};
    ssize_t len = 0;

    // 为保证读完，需循环读取。
    while (true)
    {
        bzero(readStr, sizeof(readStr));

        len = read(fd2, readStr, sizeof(readStr) - 1);
        if (-1 == len)
        {
            perror("read");


            return -1;
        }

        std::cout << readStr;

        if (0 == len) break;
    }

    std::cout << std::endl;

    close(fd2);


    unlink(filePath);


    return 0;
}
