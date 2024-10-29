#include <iostream>


void foo()
{
    std::cout << "function: " << __FUNCTION__ << std::endl;
    std::cout << "function: " << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "function: " << __func__ << std::endl;
}


int main(int argc, char const *argv[])
{
    foo();

    std::cout << "function: " << __FUNCTION__ << std::endl;
    std::cout << "function: " << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "function: " << __func__ << std::endl;


    return 0;
}
