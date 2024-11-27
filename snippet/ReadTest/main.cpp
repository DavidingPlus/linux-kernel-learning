#include <iostream>

#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd = open("/dev/second", O_RDONLY);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    int counter = 0, oldCounter = 0;

    while (true)
    {
        read(fd, &counter, sizeof(int));
        // 引入 oldCounter 是因为这个死循环是一直读，而非每一秒读一次，因此为了每秒的打印，引入 oldCounter 做比较，当 counter 更新以后才表示过了 1 秒。
        if (counter != oldCounter)
        {
            std::cout << "seconds after open /dev/second: " << counter << std::endl;

            oldCounter = counter;
        }
    }

    close(fd);


    return 0;
}
