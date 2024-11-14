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
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;
    unsigned long offset = (unsigned long)*pOffset;


    // 如果偏移量 >= mem 的大小 GLOBALFIFO_SIZE，表示已经读到末尾了。
    if (offset >= GLOBALFIFO_SIZE) return 0;
    // 如果 mem 剩余的大小不足 count，调整 count 大小，保证读到末尾。
    if (GLOBALFIFO_SIZE - offset < count) count = GLOBALFIFO_SIZE - offset;

    // 使用 copy_to_user() 函数，可能导致阻塞，因此不能使用自旋锁，应使用互斥体。
    mutex_lock(&pGlobalFifoData->m_mtx);

    // 对内核空间访问用户空间数据的合法性检测，保证传入数据的确属于用户空间。
    if (0 == access_ok(pBuf, count)) return -EFAULT;

    if (copy_to_user(pBuf, pGlobalFifoData->m_mem + offset, count))
    {
        printk(KERN_INFO "globalfifo: copy_to_user() failed.\n");


        return -EFAULT;
    }

    // 读取成功修改文件偏移指针。
    *pOffset += count;

    mutex_unlock(&pGlobalFifoData->m_mtx);

    printk(KERN_INFO "globalfifo: globalfifo_read(): %s\n", pGlobalFifoData->m_mem + offset);


    return (ssize_t)count;
}

ssize_t globalfifo_write(struct file *pFile, const char __user *pBuf, size_t count, loff_t *pOffset)
{
    struct LGlobalFifoDataT *pGlobalFifoData = (struct LGlobalFifoDataT *)pFile->private_data;
    unsigned long offset = (unsigned long)*pOffset;


    if (offset >= GLOBALFIFO_SIZE) return 0;
    if (GLOBALFIFO_SIZE - offset < count) count = GLOBALFIFO_SIZE - offset;

    mutex_lock(&pGlobalFifoData->m_mtx);

    if (0 == access_ok(pBuf, count)) return -EFAULT;

    if (copy_from_user(pGlobalFifoData->m_mem + offset, pBuf, count))
    {
        printk(KERN_INFO "globalfifo: copy_from_user() failed.\n");


        return -EFAULT;
    }

    *pOffset += count;

    mutex_unlock(&pGlobalFifoData->m_mtx);

    printk(KERN_INFO "globalfifo: globalfifo_write(): %s\n", pGlobalFifoData->m_mem + offset);


    return (ssize_t)count;
}

loff_t globalemem_llseek(struct file *pFile, loff_t offset, int orig)
{
    loff_t base;

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
