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
#include <linux/timer.h>

#include "lglobal.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Linux Kernel Module to Test Timer");


extern struct timer_list timer1, timer2;


static int __init timer_init(void)
{
    // 初始化 timer1
    timer_setup(&timer1, timerExpires, 0);

    // 向内核添加定时器。
    // 这两行等价于：mod_timer(&timer1, jiffies + 1 * HZ);
    timer1.expires = jiffies + 1 * HZ; // 1s timeout
    add_timer(&timer1);

    mod_timer(&timer2, jiffies + 2 * HZ); // 2s timeout

    printk(KERN_INFO "timer: timer init.\n");


    return 0;
}

static void __exit timer_exit(void)
{
    del_timer(&timer1);
    del_timer(&timer2);

    printk(KERN_INFO "timer: timer exit.\n");
}


module_init(timer_init);
module_exit(timer_exit);
