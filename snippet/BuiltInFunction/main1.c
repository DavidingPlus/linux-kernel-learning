#include <stdio.h>


void foo()
{
    // 内建函数 __builtin_return_address(LEVEL) 返回当前函数或其调用者的返回地址。参数 LEVEL 指定调用栈的级数，如 0 表示当前函数的返回地址，1 表示当前函数的调用者的返回地址。
    printf("function %s calling, address: %p\n", __func__, __builtin_return_address(0));
    printf("function %s calling, caller address: %p\n", __func__, __builtin_return_address(1));
}


int main()
{
    printf("function %s calling, address: %p\n", __func__, __builtin_return_address(0));
    printf("function %s calling, caller address: %p\n", __func__, __builtin_return_address(1)); // 在 main() 函数中查询 caller 的地址会段错误，因为在 C 语言层面来讲，main() 是程序入口函数。

    foo();


    return 0;
}
