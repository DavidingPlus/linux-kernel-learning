#ifndef _LFOPS_H_
#define _LFOPS_H_

#include <linux/fs.h>


int globalmem_open(struct inode *, struct file *);

int globalmem_release(struct inode *, struct file *);

ssize_t globalmem_read(struct file *, char __user *, size_t, loff_t *);

ssize_t globalmem_write(struct file *, const char __user *, size_t, loff_t *);

loff_t globalemem_llseek(struct file *, loff_t, int);

long globalmem_ioctl(struct file *, unsigned int, unsigned long);


#endif
