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
 * @details 读的语义是：每次从 globalinfo 的 mem 中从头开始读取 count 个字节，读取完毕后将读取的数据拿掉。如果 count > currentLen，则调整读取的字节为 currentLen。
 */
ssize_t globalfifo_read(struct file *, char __user *, size_t, loff_t *);

/**
 * @brief 注册 write() 函数。
 * @details 写的语义是：每次将 count 字节的数据写到 globalinfo 的 mem 末尾。如果超出内存数组大小，则多余的数据无法写入，即调整写入的字节为 GLOBALINFO_SIZE - currentLen。
 */
ssize_t globalfifo_write(struct file *, const char __user *, size_t, loff_t *);

/**
 * @brief 注册 llseek() 函数。
 * @details 在当前语义下，读和写的位置是由管道特性定死的。因此 llseek() 函数不应该被提供。
 */
// loff_t globalemem_llseek(struct file *, loff_t, int);

/**
 * @brief 注册 unlocked_ioctl() 函数。
 */
long globalfifo_ioctl(struct file *, unsigned int, unsigned long);


#endif
