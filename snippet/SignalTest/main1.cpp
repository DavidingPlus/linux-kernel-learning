#include <iostream>

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


#define MAX_SIZE BUFSIZ


void doIt(int sigNum)
{
    char data[MAX_SIZE] = {0};

    // 读取并输出 STDIN_FILENO 上的输入
    int len = read(STDIN_FILENO, &data, MAX_SIZE);

    std::cout << "input data: " << data << std::endl;
}


int main()
{
    // 启动信号驱动机制
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = doIt;
    sigemptyset(&act.sa_mask);

    sigaction(SIGIO, &act, nullptr);

    // TODO 下面代码的含义是让当前进程设置为接受 SIGIO 信号，并且告诉内核是通过异步的方式接受。在这个程序中异步的感观不明显，但确实是这样用的。想办法让其感观明显一点。

    // 设置将接收 SIGIO 和 SIGURG 信号的进程 id 或进程组 id
    fcntl(STDIN_FILENO, F_SETOWN, getpid());
    // 修改为异步通知模式
    int flag = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flag | FASYNC);

    // 最后进入一个死循环，仅为保持进程不终止，如果程序中没有这个死循会立即执行完毕
    for (;;)
    {
    }


    return 0;
}
