#include "calc.h"

#include <linux/printk.h>
#include <linux/errno.h>


int myAdd(int a, int b)
{
    return a + b;
}

int mySub(int a, int b)
{
    return a - b;
}

int myMul(int a, int b)
{
    return a * b;
}

int myDiv(int a, int b)
{
    if (0 == b)
    {
        pr_err("exp3-export: The divisor cannot be 0.\n");


        return -EINVAL;
    }

    return a / b;
}


EXPORT_SYMBOL(myAdd);
EXPORT_SYMBOL(mySub);
EXPORT_SYMBOL(myMul);
EXPORT_SYMBOL(myDiv);
