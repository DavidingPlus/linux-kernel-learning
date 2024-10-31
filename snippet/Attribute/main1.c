#include <stdio.h>
#include <stdlib.h>


// 特殊属性声明，GNU C 允许函数、变量和类型在声明的时候添加特殊属性。
// 注意需要在声明的时候加属性而不是定义的时候，所以要将声明和定义分开。
void doExit() __attribute__((__noreturn__));


int main()
{
    doExit();


    return 0;
}


void doExit()
{
    printf("function foo() with __attribute__((__noreturn__)).\n");

    // 由于上面打印了一条信息，如果没有 exit() 语句直接退出程序，编译器会认为此函数是会返回的，虽然代码里面写的 void 返回值。因此会爆警告，执行的时候也会遇到问题。
    // 事实上，exit() 函数也声明了 __attribute__((__noreturn__))，加在本函数末尾保证了函数不会返回。
    exit(0);
}
