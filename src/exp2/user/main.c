#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <sys/syscall.h>


#define __NR_mycall 451
#define LOOP_COUNT 100000


long userCompute(int op, long num1, long num2, long loopCount)
{
    volatile long result = 0;

    for (long i = 0; i < loopCount; ++i)
    {
        switch (op)
        {
            case '+':
                result += (num1 + num2) + i;
                break;

            case '-':
                result += (num1 - num2) + i;
                break;

            case '*':
                result += (num1 * num2) + i;
                break;

            case '/':
                result += (num1 / num2) + i;
                break;
        }
    }


    return result;
}

long kernelCompute(int op, long num1, long num2, long loopCount)
{
    return syscall(__NR_mycall, op, num1, num2, loopCount);
}

long timeFunc(long (*func)(int, long, long, long), int op, long num1, long num2, long loopCount, long *result)
{
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    *result = func(op, num1, num2, loopCount);
    clock_gettime(CLOCK_MONOTONIC, &end);

    long timeUs = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_nsec - start.tv_nsec) / 1000L;


    return timeUs;
}

int main()
{
    long num1 = 123;
    long num2 = 456;

    long userRes, kernelRes;

    // 用户态测试。
    long userTime = timeFunc(userCompute, '+', num1, num2, LOOP_COUNT, &userRes);

    printf("User result: %ld\n", userRes);
    printf("User time: %ld us\n", userTime);

    // 内核态测试。
    long kernelTime = timeFunc(kernelCompute, '+', num1, num2, LOOP_COUNT, &kernelRes);

    printf("Kernel result: %ld\n", kernelRes);
    printf("Kernel time: %ld us\n", kernelTime);


    return 0;
}
