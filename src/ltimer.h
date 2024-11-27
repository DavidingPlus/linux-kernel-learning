/**
 * @file ltimer.h
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 定时器回调函数的头文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#ifndef _LTIMER_H_
#define _LTIMER_H_

#include <linux/timer.h>


/**
 * @brief 定时器的回调函数。
 */
void timerHandler(struct timer_list *);


#endif
