#include <stdio.h>
#include <stdlib.h>


// do {} while(0) 语句主要用于宏定义。

// 主函数中的语句会被展开为：
// if (NULL != p)
//     free(p); p = NULL;
// else
//     ...
// 这样 else 分支没有对应的 if 语句，编译失败。并且 p = NULL 这条语句无论如何都会被执行。
#define SAFE_FREE1(p) \
    free(p);          \
    p = NULL;

// 加上括号确实能解决问题，但是由于 C 语言编程的习惯，SAFE_FREE2 在使用中末尾一般会有分号，因此会被展开为
// if (NULL != p)
//     { free(p); p = NULL; };
// else
//     ...
// 由于 ; 的存在，else 又没有 if 分支了，又编译失败。
#define SAFE_FREE2(p) \
    {                 \
        free(p);      \
        p = NULL;     \
    }

// do{} while(0) 的使用完全是为了保证宏定义的使用者能无编译错误地使用宏，它不对其使用者做任何假设。
#define SAFE_FREE3(p) \
    do                \
    {                 \
        free(p);      \
        p = NULL;     \
    } while (0) // 注意这里末尾没有 ; 号，为了和程序中的分号相对应。


int main()
{
    int *p = malloc(sizeof(int));
    if (!p)
    {
        fprintf(stderr, "Memory allocation failed\n");


        return -1;
    }


    printf("address p: %p\n", p);


    // 其实最好的解决办法是把 if 里面所有的内容不管一行还是多行都用大括号括起来，这样是从语言层面最好的解决办法。
    if (NULL != p)
        SAFE_FREE3(p);
    else
    {
    }


    return 0;
}
