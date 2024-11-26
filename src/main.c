/**
 * @file main.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 驱动程序入口文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>

#include "lglobal.h"
#include "lfops.h"
#include "ltimer.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A character device named second that logs jiffies every second and returns elapsed seconds while reading");


extern struct file_operations LSecondFops;
extern struct LSecondDataT secondData;


static int __init second_init(void)
{
    int res = alloc_chrdev_region(&secondData.m_devNumber, 0, secondData.m_devCount, secondData.m_devName);
    if (res < 0)
    {
        printk(KERN_ALERT "second: alloc_chrdev_region() failed.\n");


        return res;
    }

    secondData.m_cdev = cdev_alloc();
    if (!secondData.m_cdev)
    {
        printk(KERN_ALERT "second: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(secondData.m_cdev, &LSecondFops);

    res = cdev_add(secondData.m_cdev, secondData.m_devNumber, secondData.m_devCount);
    if (res < 0)
    {
        printk(KERN_ALERT "second: cdev_add() failed.\n");


        return res;
    }

    // 初始化定时器
    timer_setup(&secondData.m_timer, secondTimerHandler, 0);
    // 注册定时器
    secondData.m_timer.expires = jiffies + HZ;
    add_timer(&secondData.m_timer);

    printk(KERN_INFO "second: second init!\n");


    return 0;
}

static void __exit second_exit(void)
{
    // 销毁定时器
    del_timer(&secondData.m_timer);

    cdev_del(secondData.m_cdev);

    unregister_chrdev_region(secondData.m_devNumber, secondData.m_devCount);

    printk(KERN_INFO "second: second exit!\n");
}


module_init(second_init);
module_exit(second_exit);
