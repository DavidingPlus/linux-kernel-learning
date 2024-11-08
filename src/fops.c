#include "fops.h"

#include <linux/uaccess.h>

#include "main.h"


extern struct LGlobalMemDataT globalmemData;


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

// TODO 修改读写逻辑，兼顾 offp 文件偏移指针。
ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
    if (count > GLOBALMEM_SIZE - 1) return -ENOMEM;
    if (count < 0) return -EINVAL;

    // 对内核空间访问用户空间数据的合法性检测，保证传入数据的确属于用户空间。
    if (0 == access_ok(buf, count)) return -EFAULT;

    if (copy_to_user(buf, globalmemData.m_mem, count))
    {
        printk(KERN_INFO "globalmem: copy_to_user() failed.\n");


        return -EFAULT;
    }

    printk(KERN_INFO "globalmem: driver globalmem read: %s\n", globalmemData.m_mem);


    return (ssize_t)count;
}

ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
    if (count > GLOBALMEM_SIZE - 1) return -ENOMEM;
    if (count < 0) return -EINVAL;

    if (0 == access_ok(buf, count)) return -EFAULT;

    if (copy_from_user(globalmemData.m_mem, buf, count))
    {
        printk(KERN_INFO "globalmem: copy_from_user() failed.\n");


        return -EFAULT;
    }

    printk(KERN_INFO "globalmem: driver globalmem write: %s\n", globalmemData.m_mem);


    return (ssize_t)count;
}

// TODO
loff_t globalemem_llseek(struct file *filp, loff_t offset, int orig)
{
    return (loff_t)0;
}

long globalmem_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return (long)0;
}
