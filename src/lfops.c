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
#include <linux/poll.h>
#include <uapi/asm-generic/siginfo.h>

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
    // 将文件从异步通知队列中删除。
    globalfifo_fasync(-1, pFile, 0);

    printk(KERN_INFO "globalfifo: globalfifo_release()\n");


    return 0;
}

ssize_t globalfifo_read(struct file *pFile, char __user *pBuf, size_t count, loff_t *pOffset)
{
    // ISO C90 禁止混合声明和代码。在 C99 标准之前，所有声明都必须位于块中的任何语句之前。
    ssize_t res = 0;
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;
    // 定义等待队列元素。
    DECLARE_WAITQUEUE(wait, current);


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
        // 调度其他进程之前解锁。
        mutex_unlock(&pGlobalFifoData->m_mtx);
        // 处理好以后调度其他进程。
        schedule();

        // 判断是否由信号唤醒。
        if (signal_pending(current))
        {
            res = -ERESTARTSYS;
            // 单独设置一个 out2 是因为这里不需要再次释放互斥体了。
            goto out2;
        }

        // 重新加回锁。
        mutex_lock(&pGlobalFifoData->m_mtx);
    }

    // 如果想要读的 count 大于 currentLen，调整 count。
    if (count > pGlobalFifoData->m_currentLen) count = pGlobalFifoData->m_currentLen;

    // copy_to_user() 和 copy_from_user() 包含 access_ok() 的检测，此处省去显式检测。
    if (copy_to_user(pBuf, pGlobalFifoData->m_mem, count))
    {
        res = -EFAULT;

        printk(KERN_INFO "globalfifo: copy_to_user() failed.\n");

        goto out;
    }
    else
    {
        // 读取成功，修改数据。
        memcpy(pGlobalFifoData->m_mem, pGlobalFifoData->m_mem + count, pGlobalFifoData->m_currentLen - count);

        pGlobalFifoData->m_currentLen -= count;
        res = count;

        // 除此之外，还要唤醒写等待队列的进程。
        wake_up_interruptible(&pGlobalFifoData->m_writeWaitQueueHead);

        // 产生异步可写信号。
        if (pGlobalFifoData->m_fasync)
        {
            kill_fasync(&pGlobalFifoData->m_fasync, SIGIO, POLL_OUT);

            printk(KERN_INFO "globalfifo: %s() kill SIGIO\n", __func__);
        }

        printk(KERN_INFO "globalfifo: globalfifo_read(): read %ld bytes, currentLen: %d\n", count, pGlobalFifoData->m_currentLen);
    }


out:
    mutex_unlock(&pGlobalFifoData->m_mtx);

out2:
    remove_wait_queue(&pGlobalFifoData->m_readWaitQueueHead, &wait);
    __set_current_state(TASK_RUNNING);


    return res;
}

// 写的过程完全类似，根据管道的语义画个示意图就明白了。
ssize_t globalfifo_write(struct file *pFile, const char __user *pBuf, size_t count, loff_t *pOffset)
{
    ssize_t res = 0;
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;
    DECLARE_WAITQUEUE(wait, current);


    mutex_lock(&pGlobalFifoData->m_mtx);

    add_wait_queue(&pGlobalFifoData->m_writeWaitQueueHead, &wait);

    while (pGlobalFifoData->m_currentLen == GLOBALFIFO_SIZE)
    {
        if (pFile->f_flags & O_NONBLOCK)
        {
            res = -EAGAIN;

            goto out;
        }

        __set_current_state(TASK_INTERRUPTIBLE);

        mutex_unlock(&pGlobalFifoData->m_mtx);

        schedule();

        if (signal_pending(current))
        {
            res = -ERESTARTSYS;

            goto out2;
        }

        mutex_lock(&pGlobalFifoData->m_mtx);
    }

    if (count > GLOBALFIFO_SIZE - pGlobalFifoData->m_currentLen) count = GLOBALFIFO_SIZE - pGlobalFifoData->m_currentLen;

    if (copy_from_user(pGlobalFifoData->m_mem + pGlobalFifoData->m_currentLen, pBuf, count))
    {
        res = -EFAULT;

        printk(KERN_INFO "globalfifo: copy_from_user() failed.\n");

        goto out;
    }
    else
    {
        pGlobalFifoData->m_currentLen += count;
        res = count;

        wake_up_interruptible(&pGlobalFifoData->m_readWaitQueueHead);

        if (pGlobalFifoData->m_fasync)
        {
            kill_fasync(&pGlobalFifoData->m_fasync, SIGIO, POLL_IN);

            printk(KERN_INFO "globalfifo: %s() kill SIGIO\n", __func__);
        }

        printk(KERN_INFO "globalfifo: globalfifo_write(): write %ld bytes, currentLen: %d\n", count, pGlobalFifoData->m_currentLen);
    }


out:
    mutex_unlock(&pGlobalFifoData->m_mtx);

out2:
    remove_wait_queue(&pGlobalFifoData->m_writeWaitQueueHead, &wait);
    __set_current_state(TASK_RUNNING);


    return res;
}

long globalfifo_ioctl(struct file *pFile, unsigned int cmd, unsigned long arg)
{
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;

    // 目前仅支持 FIFO_CLEAR 清空操作。
    switch (cmd)
    {
        case FIFO_CLEAR:
        {
            mutex_lock(&pGlobalFifoData->m_mtx);

            memset(pGlobalFifoData->m_mem, 0, GLOBALFIFO_SIZE);

            mutex_unlock(&pGlobalFifoData->m_mtx);

            printk("globalfifo: globalfifo_ioctl(): FIFO_CLEAR %d\n", FIFO_CLEAR);

            break;
        }

        default:
            return -EINVAL;
            break;
    }


    return 0;
}

__poll_t globalfifo_poll(struct file *pFile, struct poll_table_struct *pWait)
{
    __poll_t mask = 0;
    struct LGlobalFifoDataT *pGlobalFifoData = pFile->private_data;

    mutex_lock(&pGlobalFifoData->m_mtx);

    // 第一次调用，将进程加入等待队列。
    poll_wait(pFile, &pGlobalFifoData->m_readWaitQueueHead, pWait);
    poll_wait(pFile, &pGlobalFifoData->m_writeWaitQueueHead, pWait);

    // 第二次调用，如果满足条件，则返回 mask。
    if (0 != pGlobalFifoData->m_currentLen) mask |= POLLIN | POLLRDNORM;
    if (GLOBALFIFO_SIZE != pGlobalFifoData->m_currentLen) mask |= POLLOUT | POLLWRNORM;

    mutex_unlock(&pGlobalFifoData->m_mtx);


    return mask;
}

int globalfifo_fasync(int fd, struct file *pFile, int mode)
{
    struct LGlobalFifoDataT *pGlobalFifoData = pFile->private_data;


    return fasync_helper(fd, pFile, mode, &pGlobalFifoData->m_fasync);
}
