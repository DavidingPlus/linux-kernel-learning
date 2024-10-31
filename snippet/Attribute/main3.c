#include <stdio.h>


// 编译器对结构体成员及变量对齐的目的是为了更快地访问结构体成员及变量占据的内存。例如，对于一个 32 位的整型变量，若以 4 字节方式存放（即低两位地址为 00），则 CPU 在一个总线周期内就可以读取 32 位；否则，CPU 需要两个总线周期才能读取 32 位。
struct LDataT
{
    char a;
    int b;
}; // 默认以 4 字节为单位对齐。

struct LDataT2
{
    char a;
    int b;
} __attribute__((aligned(16))); // aligned() 属性要求内存对齐的大小必须为 2 的倍数。

struct LDataT3
{
    char a;
    int b;
} __attribute__((packed)); // packed 属性作用于变量和类型。用于变量或结构体成员时表示使用最小可能的对齐，用于枚举、结构体或联合体类型时表示该类型使用最小的内存。


int main()
{
    // 需开启 gcc -Wall 编译选项，对应 CMake 中就是 add_definitions ("-Wall")。
    int a __attribute__((unused));


    printf("sizeof LDataT: %ld\n", sizeof(struct LDataT));   // 8
    printf("sizeof LDataT2: %ld\n", sizeof(struct LDataT2)); // 16
    printf("sizeof LDataT3: %ld\n", sizeof(struct LDataT3));


    return 0;
}
