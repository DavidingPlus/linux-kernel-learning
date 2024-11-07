#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>


int main()
{
    int fd = open("/dev/chrdev", O_RDWR);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    char readStr[] = "hello linux kernel";

    int len = strlen(readStr);

    write(fd, readStr, len);
    memset(readStr, '\0', len);
    read(fd, readStr, len);

    std::cout << "readStr is: " << readStr << std::endl;


    return 0;
}
