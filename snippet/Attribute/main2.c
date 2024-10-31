#include <stdio.h>
#include <stdarg.h>


// 使用 __attribute__((format(printf, 1, 2))) 检查格式
// 第 1 个参数是格式串 fmt，从第 2 个参数开始都会根据 printf() 函数的格式串规则检查参数。
void doPrint(const char *fmt, ...) __attribute__((format(printf, 1, 2)));


int main()
{
    doPrint("Hello, %s! The number is %d.\n", "World", 42);

    // 这一行会在编译时触发格式不匹配的警告 mismatch 不匹配 %d
    // doPrint("Number only: %d\n", "mismatch");

    return 0;
}


void doPrint(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
