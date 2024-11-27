/**
 * @file ltimer.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 定时器回调函数的源文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include "ltimer.h"

#include "lglobal.h"


extern struct LSecondDataT secondData;


void timerHandler(struct timer_list *timer)
{
    if (timer != &secondData.m_timer)
    {
        printk(KERN_WARNING "second: timer unknown %p", timer);


        return;
    }

    printk(KERN_INFO "timer: current jiffies is %ld\n", jiffies);

    mod_timer(timer, jiffies + HZ);

    // 原子变量自增
    atomic_inc(&secondData.m_counter);
}
