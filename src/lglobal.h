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

#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/mutex.h>


/**
 * @brief 全局内存的大小。
 */
#define GLOBALFIFO_SIZE 0x1000

/**
 * @brief 清空全局内存，用于 ioctal() 的 I/O 控制命令。
 */
#define MEM_CLEAR _IO('c', 0)


/**
 * @brief 全局内存的数据结构体类型。
 */
struct LGlobalFifoDataT
{
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

    /**
     * @brief 全局内存数组。
     */
    unsigned char m_mem[GLOBALFIFO_SIZE];

    /**
     * @brief 互斥体。
     */
    struct mutex m_mtx;
};


#endif
