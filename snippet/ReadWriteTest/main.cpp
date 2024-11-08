#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>


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

    // 如果不重置文件偏移指针，就读，那读出来包是空的。
    lseek(fd, 0, SEEK_SET);

    bzero(readStr, sizeof(readStr));
    read(fd, readStr, len);

    std::cout << "readStr is: " << readStr << std::endl;


    return 0;
}