#include "fops.h"

#include <linux/uaccess.h>


char kernelStr[MAX_SIZE] = {0};


int globalmem_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "globalmem: driver globalmem open.\n");


    return 0;
}

int globalmem_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "globalmem: driver globalmem release.\n");


    return 0;
}

ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
    if (count > MAX_SIZE - 1) return -ENOMEM;
    if (count < 0) return -EINVAL;


    if (0 != copy_from_user(kernelStr, buf, count))
    {
        printk(KERN_INFO "globalmem: copy_from_user() failed.\n");


        return -EFAULT;
    }

    printk(KERN_INFO "globalmem: driver globalmem write: %s\n", kernelStr);


    return (ssize_t)count;
}

ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
    if (count > MAX_SIZE - 1) return -ENOMEM;
    if (count < 0) return -EINVAL;


    if (0 != copy_to_user(buf, kernelStr, count))
    {
        printk(KERN_INFO "globalmem: copy_to_user() failed.\n");


        return -EFAULT;
    }

    printk(KERN_INFO "globalmem: driver globalmem read: %s\n", kernelStr);


    return (ssize_t)count;
}
