#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define FIFO_CLEAR _IO('c', 0)


int main()
{
    int fd = open("/dev/globalfifo", O_RDWR);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    char readStr[] = "hello globalfifo module.";

    int len = strlen(readStr);

    write(fd, readStr, len);

    // 使用 ioctl() 清空 globalfifo 的内存数据。
    ioctl(fd, FIFO_CLEAR);

    std::cout << "FIFO_CLEAR: " << FIFO_CLEAR << std::endl;
    std::cout << "FIFO_CLEAR's type: " << (char)_IOC_TYPE(FIFO_CLEAR) << std::endl; // c
    std::cout << "FIFO_CLEAR's nr: " << _IOC_NR(FIFO_CLEAR) << std::endl;           // 0


    lseek(fd, 0, SEEK_SET);

    bzero(readStr, sizeof(readStr));
    read(fd, readStr, len);

    std::cout << "readStr is: " << readStr << std::endl; // 空


    return 0;
}
