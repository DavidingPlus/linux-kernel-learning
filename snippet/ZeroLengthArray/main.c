#include <stdio.h>


// C 语言的结构体不支持在声明的时候就做初始化操作，只有在实例化对象的时候初始化。
struct LDataT
{

    int m_len;

    // char m_data[0] 仅仅意味着程序中通过 LDataT 结构体实例的 data[index] 成员可以访问 m_len 之后的第 index 个地址，它并没有为 data[] 数组分配内存，因此 sizeof(struct LDataT) == sizeof(int)。
    // 零长度数组的存在，可以使得我们可以通过 m_data 指针访问内存地址后面的数据，例如这里就可以访问 m_len 以后的数据，当然这里超出结构体内存范围了，因此数据是随机的。
    char m_data[0];
};


int main()
{
    // 四种初始化结构体的方法，见：https://blog.csdn.net/ericbar/article/details/79567108

    // 这是 C 语言的风格，在写驱动注册函数的时候经常用到。
    struct LDataT dt = {
        .m_len = 4,
    };


    printf("sizeof LDataT: %ld\n", sizeof(struct LDataT));
    printf("sizeof int: %ld\n", sizeof(int));


    for (int i = 0; i < 100; ++i)
    {
        printf("%02x\n", dt.m_data[i]);
    }


    return 0;
}
