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

    // 使用 AIO 读

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

    // 使用 aio_error()，轮询查询结果
    while (aio_error(&aio) == EINPROGRESS) continue;

    res = aio_return(&aio);
    if (-1 == res) ERR_EXIT("aio_return");

    std::cout << "res: " << res << std::endl;
    std::cout << "aio_read: " << (char *)aio.aio_buf << std::endl;

    remove("file.txt");


    return 0;
}
