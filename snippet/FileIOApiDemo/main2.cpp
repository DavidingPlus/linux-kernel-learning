// 使用标准 C 库函数。
#include <iostream>
#include <cstring>


#define MAX_SIZE 10


int main()
{
    const char *filePath = "hello.txt";
    const char *writeStr = "He\nllo, software weekly.";

    FILE *file = fopen(filePath, "w");
    if (!file)
    {
        perror("fopen");


        return -1;
    }

    fputs(writeStr, file);

    fclose(file);


    FILE *file2 = fopen(filePath, "r");
    if (!file2)
    {
        perror("fopen");


        return -1;
    }

    char readStr[MAX_SIZE] = {0};

    while (true)
    {
        bzero(readStr, sizeof(readStr));

        fgets(readStr, sizeof(readStr) - 1, file2);
        if (ferror(file2))
        {
            perror("fgets");


            return -1;
        }

        std::cout << readStr;

        if (feof(file2)) break;
    }

    std::cout << std::endl;

    fclose(file2);


    remove(filePath);


    return 0;
}
