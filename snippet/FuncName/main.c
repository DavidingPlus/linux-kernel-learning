#include <stdio.h>


void foo()
{
    printf("function: %s\n", __FUNCTION__);        // 保存函数在源码中的名字。
    printf("function: %s\n", __PRETTY_FUNCTION__); // 保存带语言特色的名字。C 语言的 __FUNCTION__ 和 __PRETTY_FUNCTION__ 一样，C++ 不一样，具有特色。
    printf("function: %s\n", __func__);            // C99 标准支持，推荐使用。
}


int main(int argc, char const *argv[])
{
    foo();

    printf("function: %s\n", __FUNCTION__);
    printf("function: %s\n", __PRETTY_FUNCTION__);
    printf("function: %s\n", __func__);


    return 0;
}
