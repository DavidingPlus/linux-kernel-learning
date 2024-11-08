#include "lfops.h"

#include <linux/uaccess.h>

#include "lglobal.h"


extern struct LGlobalMemDataT globalmemData;


int globalmem_open(struct inode *inode, struct file *filp)
{
    // 为了练习，使用文件私有数据。
    filp->private_data = globalmemData.m_mem;

    printk(KERN_INFO "globalmem: globalmem_open()\n");


    return 0;
}

int globalmem_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "globalmem: globalmem_release()\n");


    return 0;
}

ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
    // ISO C90 禁止混合声明和代码。在 C99 标准之前，所有声明都必须位于块中的任何语句之前。
    unsigned char *mem = (unsigned char *)filp->private_data;
    unsigned long offset = (unsigned long)*offp;


    // 如果偏移量 >= mem 的大小 GLOBALMEM_SIZE，表示已经读到末尾了。
    if (offset >= GLOBALMEM_SIZE) return 0;
    // 如果 mem 剩余的大小不足 count，调整 count 大小，保证读到末尾。
    if (GLOBALMEM_SIZE - offset < count) count = GLOBALMEM_SIZE - offset;

    // 对内核空间访问用户空间数据的合法性检测，保证传入数据的确属于用户空间。
    if (0 == access_ok(buf, count)) return -EFAULT;

    if (copy_to_user(buf, mem + offset, count))
    {
        printk(KERN_INFO "globalmem: copy_to_user() failed.\n");


        return -EFAULT;
    }

    // 读取成功修改文件偏移指针
    *offp += count;

    printk(KERN_INFO "globalmem: globalmem_read(): %s\n", mem + offset);


    return (ssize_t)count;
}

ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp)
{
    unsigned char *mem = (unsigned char *)filp->private_data;
    unsigned long offset = (unsigned long)*offp;


    if (offset >= GLOBALMEM_SIZE) return 0;
    if (GLOBALMEM_SIZE - offset < count) count = GLOBALMEM_SIZE - offset;

    if (0 == access_ok(buf, count)) return -EFAULT;

    if (copy_from_user(mem + offset, buf, count))
    {
        printk(KERN_INFO "globalmem: copy_from_user() failed.\n");


        return -EFAULT;
    }

    *offp += count;

    printk(KERN_INFO "globalmem: globalmem_write(): %s\n", mem + offset);


    return (ssize_t)count;
}

loff_t globalemem_llseek(struct file *filp, loff_t offset, int orig)
{
    loff_t base;

    switch (orig)
    {
        case SEEK_SET:
            base = 0;
            break;

        case SEEK_CUR:
            base = filp->f_pos;
            break;

        case SEEK_END:
            base = GLOBALMEM_SIZE;
            break;

        default:
            return -EINVAL;
            break;
    }

    if (base + offset < 0 || base + offset >= GLOBALMEM_SIZE) return -EINVAL;

    filp->f_pos = base + offset;

    printk(KERN_INFO "globalmem: globalemem_llseek(): %lld\n", filp->f_pos);


    return filp->f_pos;
}

// TODO
long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return (long)0;
}
