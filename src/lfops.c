/**
 * @file lfops.c
 * @author DavidingPlus (davidingplus@qq.com)
 * @brief 向文件系统注册的回调函数的源文件。
 *
 * Copyright (c) 2024 电子科技大学 刘治学
 *
 */

#include "lfops.h"


extern struct LSecondDataT secondData;


int second_open(struct inode *pInode, struct file *pFile)
{
    pFile->private_data = &secondData;

    printk(KERN_INFO "second: second_open()\n");


    return 0;
}


int second_release(struct inode *pInode, struct file *pFile)
{
    printk(KERN_INFO "second: second_release()\n");


    return 0;
}


ssize_t second_read(struct file *pFile, char __user *pBuf, size_t count, loff_t *pOffset)
{
    printk(KERN_INFO "second: second_read()\n");


    return (ssize_t)0;
}
