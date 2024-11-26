/**
 * @file lglobal.h
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 定义宏和全局变量等的头文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#ifndef _LGLOBAL_H_
#define _LGLOBAL_H_

#include <linux/timer.h>


/**
 * @brief 全局数据的结构体类型。
 */
struct LSecondDataT
{
    /**
     * @brief 定时器。
     */
    struct timer_list m_timer;

    /**
     * @brief 描述字符设备的 cdev 结构体指针。
     */
    struct cdev *m_cdev;

    /**
     * @brief 设备号。
     */
    dev_t m_devNumber;

    /**
     * @brief 需注册的设备的个数。
     */
    int m_devCount;

    /**
     * @brief 设备名。
     */
    const char *m_devName;
};


#endif
