/**
 * @file lfops.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 向文件系统注册的回调函数的源文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include "lfops.h"

#include <linux/uaccess.h>

#include "lglobal.h"


extern struct LGlobalMemDataT globalmemData;


int globalmem_open(struct inode *pInode, struct file *pFile)
{
    // 为了练习，使用文件私有数据。
    pFile->private_data = &globalmemData;

    printk(KERN_INFO "globalmem: globalmem_open()\n");


    return 0;
}

int globalmem_release(struct inode *pInode, struct file *pFile)
{
    printk(KERN_INFO "globalmem: globalmem_release()\n");


    return 0;
}

ssize_t globalmem_read(struct file *pFile, char __user *pBuf, size_t count, loff_t *pOffset)
{
    // ISO C90 禁止混合声明和代码。在 C99 标准之前，所有声明都必须位于块中的任何语句之前。
    struct LGlobalMemDataT *pGlobalMemData = (struct LGlobalMemDataT *)pFile->private_data;
    unsigned long offset = (unsigned long)*pOffset;


    // 如果偏移量 >= mem 的大小 GLOBALMEM_SIZE，表示已经读到末尾了。
    if (offset >= GLOBALMEM_SIZE) return 0;
    // 如果 mem 剩余的大小不足 count，调整 count 大小，保证读到末尾。
    if (GLOBALMEM_SIZE - offset < count) count = GLOBALMEM_SIZE - offset;

    // 使用 copy_to_user() 函数，可能导致阻塞，因此不能使用自旋锁，应使用互斥体。
    mutex_lock(&pGlobalMemData->m_mtx);

    // 对内核空间访问用户空间数据的合法性检测，保证传入数据的确属于用户空间。
    if (0 == access_ok(pBuf, count)) return -EFAULT;

    if (copy_to_user(pBuf, pGlobalMemData->m_mem + offset, count))
    {
        printk(KERN_INFO "globalmem: copy_to_user() failed.\n");


        return -EFAULT;
    }

    // 读取成功修改文件偏移指针。
    *pOffset += count;

    mutex_unlock(&pGlobalMemData->m_mtx);

    printk(KERN_INFO "globalmem: globalmem_read(): %s\n", pGlobalMemData->m_mem + offset);


    return (ssize_t)count;
}

ssize_t globalmem_write(struct file *pFile, const char __user *pBuf, size_t count, loff_t *pOffset)
{
    struct LGlobalMemDataT *pGlobalMemData = (struct LGlobalMemDataT *)pFile->private_data;
    unsigned long offset = (unsigned long)*pOffset;


    if (offset >= GLOBALMEM_SIZE) return 0;
    if (GLOBALMEM_SIZE - offset < count) count = GLOBALMEM_SIZE - offset;

    mutex_lock(&pGlobalMemData->m_mtx);

    if (0 == access_ok(pBuf, count)) return -EFAULT;

    if (copy_from_user(pGlobalMemData->m_mem + offset, pBuf, count))
    {
        printk(KERN_INFO "globalmem: copy_from_user() failed.\n");


        return -EFAULT;
    }

    *pOffset += count;

    mutex_unlock(&pGlobalMemData->m_mtx);

    printk(KERN_INFO "globalmem: globalmem_write(): %s\n", pGlobalMemData->m_mem + offset);


    return (ssize_t)count;
}

loff_t globalemem_llseek(struct file *pFile, loff_t offset, int orig)
{
    loff_t base;

    // orig 即用户层中的 whence 起始位置。
    switch (orig)
    {
        case SEEK_SET:
            base = 0;
            break;

        case SEEK_CUR:
            base = pFile->f_pos;
            break;

        case SEEK_END:
            base = GLOBALMEM_SIZE;
            break;

        default:
            return -EINVAL;
            break;
    }

    if (base + offset < 0 || base + offset >= GLOBALMEM_SIZE) return -EINVAL;

    pFile->f_pos = base + offset;

    printk(KERN_INFO "globalmem: globalemem_llseek(): %lld\n", pFile->f_pos);


    return pFile->f_pos;
}

long globalmem_ioctl(struct file *pFile, unsigned int cmd, unsigned long arg)
{
    struct LGlobalMemDataT *pGlobalMemData = (struct LGlobalMemDataT *)pFile->private_data;

    // 目前仅支持 MEM_CLEAR 清空操作。
    switch (cmd)
    {
        case MEM_CLEAR:
        {
            mutex_lock(&pGlobalMemData->m_mtx);

            memset(pGlobalMemData->m_mem, 0, GLOBALMEM_SIZE);

            mutex_unlock(&pGlobalMemData->m_mtx);

            printk("globalmem: globalmem_ioctl(): MEM_CLEAR %d\n", MEM_CLEAR);

            break;
        }

        default:
            return -EINVAL;
            break;
    }


    return 0;
}
