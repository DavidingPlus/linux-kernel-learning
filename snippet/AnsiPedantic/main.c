#include <stdio.h>


struct LDataT
{

    int m_len;

    char m_data[0];
};


int main()
{
    // -ansi：启用 ANSI C 标准（等同于 -std=c90），并关闭 GNU C 的一些扩展功能。例如，这会禁用 GNU 内置的 inline、typeof 等非标准特性。这有助于确保代码符合 ANSI C 标准，增强移植性。

    // -pedantic：在启用标准模式时，启用严格的语法检查和警告，确保代码完全符合标准。例如，如果使用了不完全符合标准的写法，编译器会发出警告或错误。对于 GNU 扩展功能的使用，这会触发警告。


    return 0;
}
