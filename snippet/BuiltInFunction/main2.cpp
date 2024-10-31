#include <iostream>


#define a 1


int main()
{
    const int b = 2;
    constexpr long c = 3;
    double d = 3.14;


    std::cout << "a is constexpr: " << __builtin_constant_p(a) << std::endl; // 1
    std::cout << "b is constexpr: " << __builtin_constant_p(b) << std::endl; // 1
    std::cout << "c is constexpr: " << __builtin_constant_p(c) << std::endl; // 1
    std::cout << "d is constexpr: " << __builtin_constant_p(d) << std::endl; // 0


    return 0;
}
