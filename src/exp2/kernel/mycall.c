#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/ktime.h>


SYSCALL_DEFINE4(mycall, int, op, long, a, long, b, long, loopCount)
{
    u64 start, end;
    long i;
    volatile long result = 0;


    if (loopCount <= 0) return -EINVAL;

    if ('/' == op && 0 == b) return -EINVAL;


    printk(KERN_INFO "mycall: started\n");

    start = ktime_get_ns();

    for (i = 0; i < loopCount; ++i)
    {
        switch (op)
        {
            case '+':
                result += (a + b) + i;
                break;

            case '-':
                result += (a - b) + i;
                break;

            case '*':
                result += (a * b) + i;
                break;

            case '/':
                result += (a / b) + i;
                break;

            default:
                return -EINVAL;
        }
    }

    end = ktime_get_ns();


    printk(KERN_INFO "mycall: ended, result=%ld\n", result);
    printk(KERN_INFO "mycall: ended, time=%llu ns\n", end - start);


    // 返回内核态纯计算的时间。
    return end - start;
}
