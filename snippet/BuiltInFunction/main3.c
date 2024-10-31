#include <stdio.h>


int checkError(int value)
{
    // 如果我们预计 value 大多数情况下为 0（即错误不常发生），可以使用 __builtin_expect 提示编译器优化正常流程路径。即我们预计 0 == value 更有可能为 true，编译器根据这个提示将正常路径（即 0 == value 时的路径）优化为更高效的执行路径，有助于在条件满足频率较高时提升性能。

    // Linux 内核中也有相关宏的定义，用于进行程序优化。

    // #include <linux/compiler.h>

    // #define likely(x) __builtin_expect(!!(x), 1)
    // #define unlikely(x) __builtin_expect(!!(x), 0)
    // #define likely_notrace(x) likely(x)
    // #define unlikely_notrace(x) unlikely(x)

    if (__builtin_expect(0 == value, 1))
    {
        // 这里是更有可能执行的代码路径
        return 0;
    }
    else
    {
        // 错误处理
        return -1;
    }
}


int main()
{


    return 0;
}
