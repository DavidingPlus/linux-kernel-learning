#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/ioctl.h>


#define MAX_SIZE 20

#define FIFO_CLEAR _IO('c', 0)


int main()
{
    // 以非阻塞方式打开 /dev/globalfifo 设备文件
    int fd = open("/dev/globalfifo", O_RDONLY | O_NONBLOCK);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    // FIFO 清空
    if (ioctl(fd, FIFO_CLEAR) < 0) std::cout << "ioctl command failed." << std::endl;

    fd_set rfds, wfds; // 读/写文件描述符集

    while (1)
    {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_SET(fd, &rfds);
        FD_SET(fd, &wfds);

        select(fd + 1, &rfds, &wfds, NULL, NULL);

        // 数据可获得
        if (FD_ISSET(fd, &rfds)) std::cout << "Poll monitor: can be read." << std::endl;
        // 数据可写入
        if (FD_ISSET(fd, &wfds)) std::cout << "Poll monitor: can be written." << std::endl;

        // 睡眠 100 毫秒
        usleep(1000 * 100);
    }

    close(fd);


    return 0;
}
