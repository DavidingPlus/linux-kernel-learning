/**
 * @file lglobal.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 定义宏和全局变量等的源文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include "lglobal.h"


struct timer_list timer1;

DEFINE_TIMER(timer2, timerExpires);


void timerExpires(struct timer_list *timer)
{
    // 给两个 timer 设置不同的过期时间。
    if (timer == &timer1)
    {
        printk(KERN_INFO "timer: timer1 is coming.\n");

        mod_timer(&timer1, jiffies + 1 * HZ); // 1s timeout
    }
    else if (timer == &timer2)
    {
        printk(KERN_INFO "timer: timer2 is coming.\n");

        timer2.expires = jiffies + 2 * HZ; // 2s timeout
        add_timer(&timer2);
    }
    else
    {
        printk(KERN_WARNING "timer: timer unknown.\n");
    }
}
