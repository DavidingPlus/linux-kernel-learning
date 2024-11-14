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
#include <linux/export.h>

#include "lfops.h"


struct file_operations globalmemFops = {
    .owner = THIS_MODULE,
    .open = globalmem_open,
    .release = globalmem_release,
    .read = globalmem_read,
    .write = globalmem_write,
    .llseek = globalemem_llseek,
    .unlocked_ioctl = globalmem_ioctl,
};

struct LGlobalMemDataT globalmemData = {
    .m_cdev = NULL,
    .m_devNumber = 0,
    .m_devCount = 1,
    .m_devName = "globalmem",
    .m_mem = {0},
};
