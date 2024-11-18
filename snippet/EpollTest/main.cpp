#include <iostream>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>


#define FIFO_CLEAR _IO('c', 0)

#define PERROR(func)  \
    do                \
    {                 \
        perror(func); \
        return -1;    \
    } while (0)


int main()
{
    int fd = open("/dev/globalfifo", O_RDONLY | O_NONBLOCK);
    if (-1 == fd) PERROR("open");

    if (ioctl(fd, FIFO_CLEAR, 0) < 0) printf("ioctl command failed\n");

    int epollFd = epoll_create(1);
    if (epollFd < 0) PERROR("epoll_create");

    struct epoll_event events;
    bzero(&events, sizeof(struct epoll_event));
    events.events = EPOLLIN | EPOLLPRI;

    int res = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &events);
    if (res < 0) PERROR("epoll_ctl");

    res = epoll_wait(epollFd, &events, 1, 15000);
    if (res < 0)
    {
        PERROR("epoll_wait");
    }
    else if (0 == res)
    {
        printf("No data input in FIFO within 15 seconds.\n");
    }
    else
    {
        printf("FIFO is not empty\n");
    }

    res = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &events);
    if (res < 0) PERROR("epoll_ctl");

    close(epollFd);
    close(fd);


    return 0;
}
