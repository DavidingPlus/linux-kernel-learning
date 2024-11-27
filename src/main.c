/**
 * @file main.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 驱动入口程序文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "lfops.h"
#include "lglobal.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple GlobalMem Module");


extern struct file_operations globalmemFops;
extern struct LGlobalMemDataT globalmemData;


static int __init globalmem_init(void)
{
    // 申请设备号
    int res = alloc_chrdev_region(&globalmemData.m_devNumber, 0, globalmemData.m_devCount, globalmemData.m_devName);

    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: alloc_chrdev_region() failed.\n");


        return res;
    }

    // 动态申请 cdev 内存
    globalmemData.m_cdev = cdev_alloc();
    if (!globalmemData.m_cdev)
    {
        printk(KERN_ALERT "globalmem: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    // 初始化 cdev 成员
    cdev_init(globalmemData.m_cdev, &globalmemFops);

    // 添加 cdev 设备
    res = cdev_add(globalmemData.m_cdev, globalmemData.m_devNumber, globalmemData.m_devCount);
    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: cdev_add() failed.\n");


        return res;
    }

    // 初始化互斥体
    // Linux 内核优化了自旋锁、信号量、互斥体、完成量等的管理，不需要显式销毁。在数据结构生命周期结束时自动释放。
    mutex_init(&globalmemData.m_mtx);

    printk(KERN_INFO "globalmem: globalmem init!\n");


    return 0;
}

static void __exit globalmem_exit(void)
{
    // 删除 cdev 设备
    cdev_del(globalmemData.m_cdev);

    // 释放设备号
    unregister_chrdev_region(globalmemData.m_devNumber, globalmemData.m_devCount);

    printk(KERN_INFO "globalmem: globalmem exit!\n");
}


module_init(globalmem_init);
module_exit(globalmem_exit);
