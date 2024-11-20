#include <iostream>

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


void doIt(int sigNum)
{
    std::cout << "receive a signal from globalfifo, signalnum: " << sigNum << std::endl;
}


int main()
{
    int fd = open("/dev/globalfifo", O_RDWR);
    if (-1 == fd)
    {
        perror("open");


        return -1;
    }

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = doIt;
    sigemptyset(&act.sa_mask);

    sigaction(SIGIO, &act, nullptr);

    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);

    for (;;)
    {
    }


    return 0;
}
