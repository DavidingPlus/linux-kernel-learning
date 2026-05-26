#include <linux/init.h>
#include <linux/module.h>


#define LOOP_COUNT 100000


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Kernel Module To Call Functions That Were Exported");


extern int myAdd(int a, int b);

extern int mySub(int a, int b);

extern int myMul(int a, int b);

extern int myDiv(int a, int b);


u64 kernelModuleCompute(int op, long num1, long num2, long loopCount)
{
    u64 start, end;
    long i;
    volatile long result = 0;


    if (loopCount <= 0) return -EINVAL;

    if ('/' == op && 0 == num2) return -EINVAL;


    printk(KERN_INFO "exp3_call: kernelModuleCompute started\n");

    start = ktime_get_ns();

    for (i = 0; i < loopCount; ++i)
    {
        switch (op)
        {
            case '+':
                result += myAdd(num1, num2) + i;
                break;

            case '-':
                result += mySub(num1, num2) + i;
                break;

            case '*':
                result += myMul(num1, num2) + i;
                break;

            case '/':
                result += myDiv(num1, num2) + i;
                break;

            default:
                return -EINVAL;
        }
    }

    end = ktime_get_ns();


    printk(KERN_INFO "exp3_call: kernelModuleCompute ended, result=%ld\n", result);


    return end - start;
}


static int __init exp3_call_init(void)
{
    long num1, num2;
    u64 kernelModuleTime;


    printk(KERN_INFO "exp3_call: module loaded\n");


    num1 = 123, num2 = 456;

    kernelModuleTime = kernelModuleCompute('+', num1, num2, LOOP_COUNT);

    printk(KERN_INFO "exp3_call: kernelModuleCompute ended, time=%llu ns\n", kernelModuleTime);


    return 0;
}

static void __exit exp3_call_exit(void)
{
    printk(KERN_INFO "exp3_call: module unloaded\n");
}


module_init(exp3_call_init);
module_exit(exp3_call_exit);
