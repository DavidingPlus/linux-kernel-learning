#ifndef _LFOPS_H_
#define _LFOPS_H_

#include <linux/fs.h>


int globalfifo_open(struct inode *, struct file *);

int globalfifo_release(struct inode *, struct file *);

ssize_t globalfifo_read(struct file *, char __user *, size_t, loff_t *);

ssize_t globalfifo_write(struct file *, const char __user *, size_t, loff_t *);

loff_t globalemem_llseek(struct file *, loff_t, int);

long globalfifo_ioctl(struct file *, unsigned int, unsigned long);


#endif
