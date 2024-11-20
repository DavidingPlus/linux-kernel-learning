#include <iostream>
#include <cstring>

#include <aio.h>
#include <fcntl.h>


#define ERR_EXIT(func) \
    do                 \
    {                  \
        perror(func);  \
        exit(1);       \
    } while (0)


int main()
{
    FILE *pFile = fopen("file.txt", "w");
    if (!pFile) ERR_EXIT("fopen");

    fputs("hello globalfifo module.", pFile);

    fclose(pFile);

    int fd = open("file.txt", O_RDONLY);
    if (-1 == fd) ERR_EXIT("open");

    struct aiocb aio;
    std::memset(&aio, 0, sizeof(aio));

    aio.aio_buf = malloc(BUFSIZ + 1);
    if (!aio.aio_buf) ERR_EXIT("malloc");

    aio.aio_fildes = fd;
    aio.aio_nbytes = BUFSIZ;
    aio.aio_offset = 0;

    int res = aio_read(&aio);
    if (-1 == res) ERR_EXIT("aio_read");

    struct aiocb *aioArr[1] = {&aio};

    // aio_suspend() 第一个参数是存放 aiocb 结构体指针的数组，第二个参数是数组的大小。
    res = aio_suspend(aioArr, sizeof(aioArr) / sizeof(aioArr[0]), nullptr);
    if (-1 == res) ERR_EXIT("aio_suspend");

    res = aio_return(&aio);
    if (-1 == res) ERR_EXIT("aio_return");

    std::cout << "res: " << res << std::endl;
    std::cout << "aio_read: " << (char *)aio.aio_buf << std::endl;

    remove("file.txt");


    return 0;
}
