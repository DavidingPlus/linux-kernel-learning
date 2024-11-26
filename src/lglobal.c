/**
 * @file lglobal.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 定义宏和全局变量等的源文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include "lglobal.h"

#include <linux/fs.h>

#include "lfops.h"


struct file_operations LSecondFops = {
    .open = second_open,
    .release = second_release,
    .read = second_read,
};

struct LSecondDataT secondData = {
    .m_cdev = NULL,
    .m_devNumber = 0,
    .m_devCount = 1,
    .m_devName = "second",
};
