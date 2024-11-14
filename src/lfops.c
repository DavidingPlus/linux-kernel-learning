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


extern struct LGlobalFifoDataT globalfifoData;


int globalfifo_open(struct inode *pInode, struct file *pFile)
{
    // 为了练习，使用文件私有数据。
    pFile->private_data = &globalfifoData;

    printk(KERN_INFO "globalfifo: globalfifo_open()\n");


    return 0;
}

int globalfifo_release(struct inode *pInode, struct file *pFile)
{
    printk(KERN_INFO "globalfifo: globalfifo_release()\n");


    return 0;
}

ssize_t globalfifo_read(struct file *pFile, char __user *pBuf, size_t count, loff_t *pOffset)
{
    // ISO C90 禁止混合声明和代码。在 C99 标准之前，所有声明都必须位于块中的任何语句之前。
    ssize_t res = 0;
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;
    unsigned long offset = (unsigned long)*pOffset;
    DECLARE_WAITQUEUE(wait, current); // 定义等待队列元素。


    // 使用 copy_to_user() 函数，可能导致阻塞，因此不能使用自旋锁，应使用互斥体。
    mutex_lock(&pGlobalFifoData->m_mtx);

    // 将任务添加到等待队列中。
    add_wait_queue(&pGlobalFifoData->m_readWaitQueueHead, &wait);

    // 判断是否可读并针对是否阻塞做针对判断。
    while (0 == pGlobalFifoData->m_currentLen)
    {
        // 非阻塞直接返回 -EAGAIN。
        if (pFile->f_flags & O_NONBLOCK)
        {
            res = -EAGAIN;

            goto out;
        }

        // 阻塞的话改变进程状态。
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&pGlobalFifoData->m_mtx); // 调度其他进程之前解锁。

        // 处理好以后调度其他进程。
        schedule();

        // 判断是否由信号唤醒。
        if (signal_pending(current))
        {
            res = -ERESTARTSYS;

            goto out2; // 单独设置一个 out2 是因为这里不需要再次释放互斥体了。
        }

        mutex_lock(&pGlobalFifoData->m_mtx); // 重新加回锁。
    }

    // 如果偏移量 >= mem 的大小 GLOBALFIFO_SIZE，表示已经读到末尾了。
    if (offset >= GLOBALFIFO_SIZE)
    {
        res = 0;

        goto out;
    }

    // 如果 mem 剩余的大小不足 count，调整 count 大小，保证读到末尾。
    if (GLOBALFIFO_SIZE - offset < count) count = GLOBALFIFO_SIZE - offset;

    // 对内核空间访问用户空间数据的合法性检测，保证传入数据的确属于用户空间。
    if (0 == access_ok(pBuf, count))
    {
        printk(KERN_INFO "globalfifo: access_ok() check failed.\n");

        res = -EFAULT;

        goto out;
    }

    if (copy_to_user(pBuf, pGlobalFifoData->m_mem + offset, count))
    {
        printk(KERN_INFO "globalfifo: copy_to_user() failed.\n");

        res = -EFAULT;

        goto out;
    }
    else
    {
        // 读取成功，修改数据。
        // TODO

        printk(KERN_INFO "globalfifo: globalfifo_read(): %s\n", pGlobalFifoData->m_mem + offset);
    }


out:
    mutex_unlock(&pGlobalFifoData->m_mtx);

out2:
    remove_wait_queue(&pGlobalFifoData->m_readWaitQueueHead, &wait);
    __set_current_state(TASK_RUNNING);


    return res;
}

ssize_t globalfifo_write(struct file *pFile, const char __user *pBuf, size_t count, loff_t *pOffset)
{
    // TODO
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
            base = GLOBALFIFO_SIZE;
            break;

        default:
            return -EINVAL;
            break;
    }

    if (base + offset < 0 || base + offset >= GLOBALFIFO_SIZE) return -EINVAL;

    pFile->f_pos = base + offset;

    printk(KERN_INFO "globalfifo: globalemem_llseek(): %lld\n", pFile->f_pos);


    return pFile->f_pos;
}

long globalfifo_ioctl(struct file *pFile, unsigned int cmd, unsigned long arg)
{
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;

    // 目前仅支持 MEM_CLEAR 清空操作。
    switch (cmd)
    {
        case MEM_CLEAR:
        {
            mutex_lock(&pGlobalFifoData->m_mtx);

            memset(pGlobalFifoData->m_mem, 0, GLOBALFIFO_SIZE);

            mutex_unlock(&pGlobalFifoData->m_mtx);

            printk("globalfifo: globalfifo_ioctl(): MEM_CLEAR %d\n", MEM_CLEAR);

            break;
        }

        default:
            return -EINVAL;
            break;
    }


    return 0;
}
