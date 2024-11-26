/**
 * @file lfops.h
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 向文件系统注册的回调函数的头文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#ifndef _LFOPS_H_
#define _LFOPS_H_

#include <linux/fs.h>


/**
 * @brief 注册 open() 函数。
 */
int second_open(struct inode *, struct file *);

/**
 * @brief 注册 release() 函数。
 */
int second_release(struct inode *, struct file *);

/**
 * @brief 注册 read() 函数。
 */
ssize_t second_read(struct file *, char __user *, size_t, loff_t *);


#endif
