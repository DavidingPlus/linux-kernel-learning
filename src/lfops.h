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
int globalfifo_open(struct inode *, struct file *);

/**
 * @brief 注册 release() 函数。
 */
int globalfifo_release(struct inode *, struct file *);

/**
 * @brief 注册 read() 函数。
 */
ssize_t globalfifo_read(struct file *, char __user *, size_t, loff_t *);

/**
 * @brief 注册 write() 函数。
 */
ssize_t globalfifo_write(struct file *, const char __user *, size_t, loff_t *);

/**
 * @brief 注册 llseek() 函数。
 */
loff_t globalemem_llseek(struct file *, loff_t, int);

/**
 * @brief 注册 unlocked_ioctl() 函数。
 */
long globalfifo_ioctl(struct file *, unsigned int, unsigned long);


#endif
