#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define MEM_CLEAR _IO('c', 0)


int main()
{
    int fd = open("/dev/globalmem", O_RDWR);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    char readStr[] = "hello globalmem module.";

    int len = strlen(readStr);

    write(fd, readStr, len);

    // 使用 ioctl() 清空 globalmem 的内存数据。
    ioctl(fd, MEM_CLEAR);

    std::cout << "MEM_CLEAR: " << MEM_CLEAR << std::endl;
    std::cout << "MEM_CLEAR's type: " << (char)_IOC_TYPE(MEM_CLEAR) << std::endl;
    std::cout << "MEM_CLEAR's nr: " << _IOC_NR(MEM_CLEAR) << std::endl;


    lseek(fd, 0, SEEK_SET);

    bzero(readStr, sizeof(readStr));
    read(fd, readStr, len);

    std::cout << "readStr is: " << readStr << std::endl; // 空


    return 0;
}
