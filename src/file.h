#ifndef _FILE_H_
#define _FILE_H_

#include <linux/fs.h>


#define MAX_BUF_SIZE 64


int chrdev_open(struct inode *, struct file *);

int chrdev_release(struct inode *, struct file *);

ssize_t chrdev_write(struct file *, const char __user *, size_t, loff_t *);

ssize_t chrdev_read(struct file *, char __user *, size_t, loff_t *);


#endif
