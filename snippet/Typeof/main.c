#include <stdio.h>


// 这样写有个小副作用，代码 min(++ia, ++ib) 会展开为((++ia) < (++ib) ? (++ia) : (++ib))，传入宏的“参数”增加两次。
#define min1(x, y) ((x) < (y) ? (x) : (y))

// 可以拿一个临时变量存储计算结果，然后再去比较。由于已经存储好了结果，因此 tempX 和 tempY 不可能是一个表达式，因此不用加上括号。上面的那个需要加上括号。
#define min2(type, x, y)               \
    ({                                 \
        type tempX = (x);              \
        type tempY = (y);              \
        tempX < tempY ? tempX : tempY; \
    })

// 当然，GNU C 扩展提供了 typeof 关键字方便获取变量的类型，因此可以再做改进。
// 宏里面写注释的时候不能把整行注释掉，否则会宏展开错误。
#define min3(x, y)                                                           \
    ({                                                                       \
        typeof(x) tempX = (x);                                               \
        typeof(y) tempY = (y);                                               \
                                                                             \
        /* 这一行的目的是检查两个变量的类型是否一致。*/ \
                                                                             \
        (void)(&tempX == &tempY);                                            \
                                                                             \
        tempX < tempY ? tempX : tempY;                                       \
    })


int main()
{
    printf("%d\n", min1(3, 4)); // 3

    printf("%d\n", min2(int, 3, 4)); // 3

    double a = 3.55, b = 4.14;

    printf("%.2f\n", min2(double, ++a, --b)); // 3.14

    printf("%.2f\n", min2(double, a++, b--)); // 3.14


    return 0;
}
