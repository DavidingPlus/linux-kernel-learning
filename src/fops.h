#ifndef _FOPS_H_
#define _FOPS_H_

#include <linux/fs.h>


#define MAX_SIZE 64


int globalmem_open(struct inode *, struct file *);

int globalmem_release(struct inode *, struct file *);

ssize_t globalmem_write(struct file *, const char __user *, size_t, loff_t *);

ssize_t globalmem_read(struct file *, char __user *, size_t, loff_t *);


#endif
