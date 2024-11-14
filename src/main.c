#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "lfops.h"
#include "lglobal.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple globalfifo Module");


extern struct file_operations globalfifoFops;
extern struct LGlobalFifoDataT globalfifoData;


static int __init globalfifo_init(void)
{
    int res = alloc_chrdev_region(&globalfifoData.m_devNumber, 0, globalfifoData.m_devCount, globalfifoData.m_devName);

    if (res < 0)
    {
        printk(KERN_ALERT "globalfifo: register_globalfifo_region() failed.\n");


        return res;
    }

    globalfifoData.m_cdev = cdev_alloc();
    if (!globalfifoData.m_cdev)
    {
        printk(KERN_ALERT "globalfifo: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(globalfifoData.m_cdev, &globalfifoFops);

    res = cdev_add(globalfifoData.m_cdev, globalfifoData.m_devNumber, globalfifoData.m_devCount);
    if (res < 0)
    {
        printk(KERN_ALERT "globalfifo: cdev_add() failed.\n");


        return res;
    }

    // 初始化互斥体
    // Linux 内核优化了自旋锁、信号量、互斥体、完成量等的管理，不需要显式销毁。在数据结构生命周期结束时自动释放。
    mutex_init(&globalfifoData.m_mtx);

    printk(KERN_INFO "globalfifo: globalfifo init!\n");


    return 0;
}

static void __exit globalfifo_exit(void)
{
    cdev_del(globalfifoData.m_cdev);

    unregister_chrdev_region(globalfifoData.m_devNumber, globalfifoData.m_devCount);

    printk(KERN_INFO "globalfifo: globalfifo exit!\n");
}


module_init(globalfifo_init);
module_exit(globalfifo_exit);
