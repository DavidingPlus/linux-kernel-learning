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

    char s[] = "hello linux kernel";

    int len = strlen(s);

    write(fd, s, len);
    memset(s, '\0', len);
    read(fd, s, len);

    std::cout << "readBuf is: " << s << std::endl;


    return 0;
}
